/* pwd - print current directory
   Copyright (C) 1994-1997, 1999-2010 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

#include "error.h"
#include "quote.h"
#include "root-dev-ino.h"
#include "system.h"
#include "xgetcwd.h"
#include <config.h>
#include <getopt.h>
#include <stdio.h>
#include <sys/types.h>

/* The official name of this program (e.g., no `g' prefix).  */
#define PROGRAM_NAME "pwd"

#define AUTHORS proper_name("Jim Meyering")

struct		file_name
{
	char	*buf;
	size_t	n_alloc;
	char	*start;
};

static struct option const longopts[] =
	{
		{"logical", no_argument, NULL, 'L'},
		{"physical", no_argument, NULL, 'P'},
		{GETOPT_HELP_OPTION_DECL},
		{GETOPT_VERSION_OPTION_DECL},
		{NULL, 0, NULL, 0}};

void	usage(int status)
{
	if (status != EXIT_SUCCESS)
		fprintf(stderr, _("Try `%s --help' for more information.\n"),
					program_name);
	else
	{
		printf(_("Usage: %s [OPTION]...\n"), program_name);
		fputs(_("\
Print the full filename of the current working directory.\n\
\n\
"),
				stdout);
		fputs(_("\
  -L, --logical   use PWD from environment, even if it contains symlinks\n\
  -P, --physical  avoid all symlinks\n\
"),
				stdout);
		fputs(HELP_OPTION_DESCRIPTION, stdout);
		fputs(VERSION_OPTION_DESCRIPTION, stdout);
		printf(USAGE_BUILTIN_WARNING, PROGRAM_NAME);
		emit_ancillary_info();
	}
	exit(status);
}

static void
file_name_free(struct file_name *p)
{
	free(p->buf);
	free(p);
}

static struct file_name *
file_name_init(void)
{
	struct file_name	*p;

	p = wrap_malloc(sizeof *p);
	/*  PATH_MAXより大きなバッファで開始します。PATH_MAXが非常に大きいシステム、
	例えばINT_MAXのようなシステムでは、注意が必要です。 */
	p->n_alloc = MIN(2 * PATH_MAX, 32 * 1024);
	p->buf = wrap_malloc(p->n_alloc);
	p->start = p->buf + (p->n_alloc - 1);
	p->start[0] = '\0';
	return (p);
}

/*長さS_LENの名前Sを、成長中のファイル名Pの前に付ける。 */
static void
file_name_prepend(struct file_name *p, char const *s, size_t s_len)
{
	size_t	n_free;
	size_t	half;
	char	*q;
	size_t	n_used;

	n_free = p->start - p->buf;
	if (n_free < 1 + s_len)
	{
		half = p->n_alloc + 1 + s_len;
	/* xnrealloc の代わりに xnmalloc+free を使用します。後者では、データを 2 回コピーすることになるからです:
	 1 回は realloc で、もう 1 回は新しいバッファの終端に合わせるためにコピーします。 xnmalloc を使用すると、1 回だけコピーします。 */
		q = xnmalloc(2, half);
		n_used = p->n_alloc - n_free;
		p->start = q + 2 * half - n_used;
		memcpy(p->start, p->buf + n_free, n_used);
		free(p->buf);
		p->buf = q;
		p->n_alloc = 2 * half;
	}
	p->start -= 1 + s_len;
	p->start[0] = '/';
	memcpy(p->start + 1, s, s_len);
}

/* N個の `/'-separated "..." で構成される文字列を (malloc'd) で返します。 */
static char *
nth_parent(size_t n)
{
	char	*buf;
	char	*p;
	size_t	i;

	buf = xnmalloc(3, n);
	p = buf;
	for (i = 0; i < n; i++)
	{
		memcpy(p, "../", 3);
		p += 3;
	}
	p[-1] = '\0';
	return (buf);
}

/*  カレントディレクトリのベースネームを決定する。DOT_SBはlstatの結果である". "を*FILE_NAMEのファイル名の前に追加する。
   DOT_SBのdev/i-nodeにマッチする`..'内のディレクトリエントリを探す。
   成功したら、*DOT_SBを..のstat情報で更新し、..にchdirし、FILE_NAMEの先頭に"/basename "を追加する。
   そうでなければ、診断結果を出して終了する。
   PARENT_HEIGHTは、`..'が開始ディレクトリより何レベル上かを示す。
   この関数が最初に呼ばれたとき（初期ディレクトリから）、PARENT_HEIGHTは1である。これは診断のためだけのものである。
   エラー時には0以外の値で終了する。 */

static void
find_dir_entry(struct stat *dot_sb, struct file_name *file_name,
		size_t parent_height)
{
	DIR			*dirp;
	int			fd;
	struct stat	parent_sb;
	bool		use_lstat;
	bool		found;
		struct dirent const *dp;
		struct stat ent_sb;
		ino_t ino;
	int			e;

	dirp = opendir("..");
;
	fd = dirfd(dirp);

	/* 親ディレクトリと子ディレクトリが異なるデバイスにある場合、
	i-nodeの数について  は有用なi-node番号のためにd_inoに頼ることはできません;
	 代わりにlstatを使用してください。  */
??	use_lstat = (parent_sb.st_dev != dot_sb->st_dev);
	found = false;
	while (1)
	{
		errno = 0;
		if ((dp = readdir_ignoring_dot_and_dotdot(dirp)) == NULL)
		{
			if (errno)
			{
				/* Save/restore errno across closedir call.  */
				e = errno;
				closedir(dirp);
				errno = e;
				/* Arrange to give a diagnostic after exiting this loop.  */
				dirp = NULL;
			}
			break ;
		}
		ino = D_INO(dp);
		if (ino == NOT_AN_INODE_NUMBER || use_lstat)
		{
			if (lstat(dp->d_name, &ent_sb) < 0)
			{
				/* Skip any entry we can't stat.  */
				continue ;
			}
			ino = ent_sb.st_ino;
		}
		if (ino != dot_sb->st_ino)
			continue ;
		/* If we're not crossing a device boundary, then a simple i-node
         match is enough.  */
		if (!use_lstat || ent_sb.st_dev == dot_sb->st_dev)
		{
			file_name_prepend(file_name, dp->d_name, _D_EXACT_NAMLEN(dp));
			found = true;
			break ;
		}
	}
	*dot_sb = parent_sb;
}

/* 現在の作業ディレクトリの完全な絶対名を構築し、それを*FILE_NAMEに格納する
getcwd関数はほぼ同じタスクを実行するが、
通常、PATH_MAXより長い名前を扱うことはできない。
 この関数にはそのような制限はない。
 しかし、GNU/Linuxのgetcwd関数は親ディレクトリのパーミッションの制限に関係なく動作するのに対し、
 この関数はパーミッションの問題やメモリ不足で失敗することが**ある。
  失敗した場合は、診断結果を出して0以外で終了する。

注意：この関数はgetcwdと似ているが
，失敗したときに診断を与えて終了するという根本的な違いがある．
私は、終了しない関数で、getcwdの代わりとして使えるものが欲しかった。
 残念ながら、良い診断を行うために呼び出し側が必要とするすべての情報を考慮すると、
 複雑さを増すだけの価値があるとは思えません。
 いずれにせよ、getcwd の置き換えは PATH_MAX の制限を越えてはいけません*。
  さもなければ、`chdir' のような関数は ENAMETOOLONG で失敗するでしょう。

 FIXME-maybe: パーミッションのために find_dir_entry が失敗した場合、
 getcwd を試してみてください。

www.DeepL.com/Translator（無料版）で翻訳しました。*/

static void
robust_getcwd(struct file_name *file_name)
{
	size_t			height;
	struct dev_ino	dev_ino_buf;
	struct dev_ino	*root_dev_ino;
	struct stat		dot_sb;

	height = 1;
	root_dev_ino = get_root_dev_ino(&dev_ino_buf);
	if (root_dev_ino == NULL)
		error(EXIT_FAILURE, errno, _("failed to get attributes of %s"),
				quote("/"));
	if (stat(".", &dot_sb) < 0)
		error(EXIT_FAILURE, errno, _("failed to stat %s"), quote("."));
	while (1)
	{
		/* If we've reached the root, we're done.  */
		if (SAME_INODE(dot_sb, *root_dev_ino))
			break ;
		find_dir_entry(&dot_sb, file_name, height++);
	}
	/* See if a leading slash is needed; file_name_prepend adds one.  */
	if (file_name->start[0] == '\0')
		file_name_prepend(file_name, "", 0);
}

/* Return PWD from the environment if it is acceptable for 'pwd -L'
   output, otherwise NULL.  */
static char *
logical_getcwd(void)
{
	struct stat	st1;
	struct stat	st2;
	char		*wd;
	char		*p;

	wd = getenv("PWD");
	/* Textual validation first.  */
	if (!wd || wd[0] != '/')
		return (NULL);
	p = wd;
	while ((p = strstr(p, "/.")))
	{
		if (!p[2] || p[2] == '/' || (p[2] == '.' && (!p[3] || p[3] == '/')))
			return (NULL);
		p++;
	}
	/* System call validation.  */
	if (stat(wd, &st1) == 0 && stat(".", &st2) == 0 && SAME_INODE(st1, st2))
		return (wd);
	return (NULL);
}

int	main(int argc, char **argv)
{
	char				*wd;
	bool				logical;
	int					c;
	struct file_name	*file_name;

	/* POSIX requires a default of -L, but most scripts expect -P.  */
	logical = (getenv("POSIXLY_CORRECT") != NULL);
	initialize_main(&argc, &argv);
	set_program_name(argv[0]);
	setlocale(LC_ALL, "");
	bindtextdomain(PACKAGE, LOCALEDIR);
	textdomain(PACKAGE);
	atexit(close_stdout);
	if (logical)
	{
		wd = logical_getcwd();
		if (wd)
		{
			puts(wd);
			exit(EXIT_SUCCESS);
		}
	}
	wd = xgetcwd();
	if (wd != NULL)
	{
		puts(wd);
		free(wd);
	}
	else
	{
		file_name = file_name_init();
		robust_getcwd(file_name);
		puts(file_name->start);
		file_name_free(file_name);
	}
	exit(EXIT_SUCCESS);
}
