#include <criterion/criterion.h>
#include "minishell.h"

void	matrix_printf(char **matrix)
{
	int	i;

	i = 0;
	if (matrix == NULL)
		return ;
	while (*(matrix + i))
	{
		ft_printf("[%s]\n", *(matrix + i));
		i++;
	}
	return ;
}

Test(split_cmd, str_null) {
	char	*str = NULL;
	char	**result = NULL;

	result = split_cmd(str);
	cr_expect(result == NULL, "Ensure returns NULL if string is empty");
}

Test(split_cmd, split_less) {
	char	*str = "ab<bc<cd<def";
	char	**result = NULL;

	result = split_cmd(str);
	cr_assert(result, "Ensure split string");
	cr_expect_str_eq(result[0], "ab", "Ensure split string, index:0");
	cr_expect_str_eq(result[1], "<", "Ensure split string, index:1");
	cr_expect_str_eq(result[2], "bc", "Ensure split string, index:2");
	cr_expect_str_eq(result[3], "<", "Ensure split string, index:3");
	cr_expect_str_eq(result[4], "cd", "Ensure split string, index:4");
	cr_expect_str_eq(result[5], "<", "Ensure split string, index:5");
	cr_expect_str_eq(result[6], "def", "Ensure split string, index:6");
	ft_matrix_free(result);
}

Test(split_cmd, split_less_start) {
	char	*str = "<ab<bc<";
	char	**result = NULL;

	result = split_cmd(str);
	cr_assert(result, "Ensure split string");
	cr_expect_str_eq(result[0], "<", "Ensure split string, index:0");
	cr_expect_str_eq(result[1], "ab", "Ensure split string, index:1");
	cr_expect_str_eq(result[2], "<", "Ensure split string, index:2");
	cr_expect_str_eq(result[3], "bc", "Ensure split string, index:3");
	cr_expect_str_eq(result[4], "<", "Ensure split string, index:4");
	ft_matrix_free(result);
}

Test(split_cmd, split_great) {
	char	*str = "ab>bc>cd>def";
	char	**result = NULL;

	result = split_cmd(str);
	cr_assert(result, "Ensure split string");
	cr_expect_str_eq(result[0], "ab", "Ensure split string, index:0");
	cr_expect_str_eq(result[1], ">", "Ensure split string, index:1");
	cr_expect_str_eq(result[2], "bc", "Ensure split string, index:2");
	cr_expect_str_eq(result[3], ">", "Ensure split string, index:3");
	cr_expect_str_eq(result[4], "cd", "Ensure split string, index:4");
	cr_expect_str_eq(result[5], ">", "Ensure split string, index:5");
	cr_expect_str_eq(result[6], "def", "Ensure split string, index:6");
	ft_matrix_free(result);
}

Test(split_cmd, split_great_start) {
	char	*str = ">ab>bc>";
	char	**result = NULL;

	result = split_cmd(str);
	cr_assert(result, "Ensure split string");
	cr_expect_str_eq(result[0], ">", "Ensure split string, index:0");
	cr_expect_str_eq(result[1], "ab", "Ensure split string, index:1");
	cr_expect_str_eq(result[2], ">", "Ensure split string, index:2");
	cr_expect_str_eq(result[3], "bc", "Ensure split string, index:3");
	cr_expect_str_eq(result[4], ">", "Ensure split string, index:4");
	ft_matrix_free(result);
}

Test(split_cmd, split_pipe) {
	char	*str = "ab|bc|cd|def";
	char	**result = NULL;

	result = split_cmd(str);
	cr_assert(result, "Ensure split string");
	cr_expect_str_eq(result[0], "ab", "Ensure split string, index:0");
	cr_expect_str_eq(result[1], "|", "Ensure split string, index:1");
	cr_expect_str_eq(result[2], "bc", "Ensure split string, index:2");
	cr_expect_str_eq(result[3], "|", "Ensure split string, index:3");
	cr_expect_str_eq(result[4], "cd", "Ensure split string, index:4");
	cr_expect_str_eq(result[5], "|", "Ensure split string, index:5");
	cr_expect_str_eq(result[6], "def", "Ensure split string, index:6");
	ft_matrix_free(result);
}

Test(split_cmd, split_pipe_start) {
	char	*str = "|ab|bc|";
	char	**result = NULL;

	result = split_cmd(str);
	cr_assert(result, "Ensure split string");
	cr_expect_str_eq(result[0], "|", "Ensure split string, index:0");
	cr_expect_str_eq(result[1], "ab", "Ensure split string, index:1");
	cr_expect_str_eq(result[2], "|", "Ensure split string, index:2");
	cr_expect_str_eq(result[3], "bc", "Ensure split string, index:3");
	cr_expect_str_eq(result[4], "|", "Ensure split string, index:4");
	ft_matrix_free(result);
}

Test(split_cmd, split_dless) {
	char	*str = "ab<<bc<<cd<<def";
	char	**result = NULL;

	result = split_cmd(str);
	cr_assert(result, "Ensure split string");
	cr_expect_str_eq(result[0], "ab", "Ensure split string, index:0");
	cr_expect_str_eq(result[1], "<<", "Ensure split string, index:1");
	cr_expect_str_eq(result[2], "bc", "Ensure split string, index:2");
	cr_expect_str_eq(result[3], "<<", "Ensure split string, index:3");
	cr_expect_str_eq(result[4], "cd", "Ensure split string, index:4");
	cr_expect_str_eq(result[5], "<<", "Ensure split string, index:5");
	cr_expect_str_eq(result[6], "def", "Ensure split string, index:6");
	ft_matrix_free(result);
}

Test(split_cmd, split_dless_start) {
	char	*str = "<<ab<<bc<<";
	char	**result = NULL;

	result = split_cmd(str);
	cr_assert(result, "Ensure split string");
	cr_expect_str_eq(result[0], "<<", "Ensure split string, index:0");
	cr_expect_str_eq(result[1], "ab", "Ensure split string, index:1");
	cr_expect_str_eq(result[2], "<<", "Ensure split string, index:2");
	cr_expect_str_eq(result[3], "bc", "Ensure split string, index:3");
	cr_expect_str_eq(result[4], "<<", "Ensure split string, index:4");
	ft_matrix_free(result);
}

Test(split_cmd, split_dgreat) {
	char	*str = "ab>>bc>>cd>>def";
	char	**result = NULL;

	result = split_cmd(str);
	cr_assert(result, "Ensure split string");
	cr_expect_str_eq(result[0], "ab", "Ensure split string, index:0");
	cr_expect_str_eq(result[1], ">>", "Ensure split string, index:1");
	cr_expect_str_eq(result[2], "bc", "Ensure split string, index:2");
	cr_expect_str_eq(result[3], ">>", "Ensure split string, index:3");
	cr_expect_str_eq(result[4], "cd", "Ensure split string, index:4");
	cr_expect_str_eq(result[5], ">>", "Ensure split string, index:5");
	cr_expect_str_eq(result[6], "def", "Ensure split string, index:6");
	ft_matrix_free(result);
}

Test(split_cmd, split_dgreat_start) {
	char	*str = ">>ab>>bc>>";
	char	**result = NULL;

	result = split_cmd(str);
	cr_assert(result, "Ensure split string");
	cr_expect_str_eq(result[0], ">>", "Ensure split string, index:0");
	cr_expect_str_eq(result[1], "ab", "Ensure split string, index:1");
	cr_expect_str_eq(result[2], ">>", "Ensure split string, index:2");
	cr_expect_str_eq(result[3], "bc", "Ensure split string, index:3");
	cr_expect_str_eq(result[4], ">>", "Ensure split string, index:4");
	ft_matrix_free(result);
}

Test(split_cmd, split_redirection_seq) {
	char	*str = "<<<a<b>>ok<<<<";
	char	**result = NULL;

	result = split_cmd(str);
	cr_assert(result, "Ensure split string");
	cr_expect_str_eq(result[0], "<<", "Ensure split string, index:0");
	cr_expect_str_eq(result[1], "<", "Ensure split string, index:1");
	cr_expect_str_eq(result[2], "a", "Ensure split string, index:2");
	cr_expect_str_eq(result[3], "<", "Ensure split string, index:3");
	cr_expect_str_eq(result[4], "b", "Ensure split string, index:4");
	cr_expect_str_eq(result[5], ">>", "Ensure split string, index:5");
	cr_expect_str_eq(result[6], "ok", "Ensure split string, index:6");
	cr_expect_str_eq(result[7], "<<", "Ensure split string, index:7");
	cr_expect_str_eq(result[8], "<<", "Ensure split string, index:8");
	ft_matrix_free(result);
}

Test(split_cmd, split_pipe_redirection_seq) {
	char	*str = "<<<ab||cdef>>ok<<|<<";
	char	**result = NULL;

	result = split_cmd(str);
	cr_assert(result, "Ensure split string");
	cr_expect_str_eq(result[0], "<<", "Ensure split string, index:0");
	cr_expect_str_eq(result[1], "<", "Ensure split string, index:1");
	cr_expect_str_eq(result[2], "ab", "Ensure split string, index:2");
	cr_expect_str_eq(result[3], "|", "Ensure split string, index:3");
	cr_expect_str_eq(result[4], "|", "Ensure split string, index:4");
	cr_expect_str_eq(result[5], "cdef", "Ensure split string, index:5");
	cr_expect_str_eq(result[6], ">>", "Ensure split string, index:6");
	cr_expect_str_eq(result[7], "ok", "Ensure split string, index:7");
	cr_expect_str_eq(result[8], "<<", "Ensure split string, index:8");
	cr_expect_str_eq(result[9], "|", "Ensure split string, index:9");
	cr_expect_str_eq(result[10], "<<", "Ensure split string, index:10");
	ft_matrix_free(result);
}

Test(split_cmd, space) {
	char	*str = "ls    -la";
	char	**result = NULL;

	result = split_cmd(str);
	cr_assert(result, "Ensure split string");
	cr_expect_str_eq(result[0], "ls", "Ensure split string, index:0");
	cr_expect_str_eq(result[1], "-la", "Ensure split string, index:1");
	ft_matrix_free(result);
}

Test(split_cmd, space_pipe) {
	char	*str = "ls   |    cat |    ls";
	char	**result = NULL;

	result = split_cmd(str);
	cr_assert(result, "Ensure split string");
	cr_expect_str_eq(result[0], "ls", "Ensure split string, index:0");
	cr_expect_str_eq(result[1], "|", "Ensure split string, index:1");
	cr_expect_str_eq(result[2], "cat", "Ensure split string, index:2");
	cr_expect_str_eq(result[3], "|", "Ensure split string, index:3");
	cr_expect_str_eq(result[4], "ls", "Ensure split string, index:4");
	ft_matrix_free(result);
}

Test(split_cmd, space_pipe_redirect) {
	char	*str = "<  << ab ||   cdef>>o k<<|<<";
	char	**result = NULL;

	result = split_cmd(str);
	cr_assert(result, "Ensure split string");
	cr_expect_str_eq(result[0], "<", "Ensure split string, index:0");
	cr_expect_str_eq(result[1], "<<", "Ensure split string, index:1");
	cr_expect_str_eq(result[2], "ab", "Ensure split string, index:2");
	cr_expect_str_eq(result[3], "|", "Ensure split string, index:3");
	cr_expect_str_eq(result[4], "|", "Ensure split string, index:4");
	cr_expect_str_eq(result[5], "cdef", "Ensure split string, index:5");
	cr_expect_str_eq(result[6], ">>", "Ensure split string, index:6");
	cr_expect_str_eq(result[7], "o", "Ensure split string, index:7");
	cr_expect_str_eq(result[8], "k", "Ensure split string, index:8");
	cr_expect_str_eq(result[9], "<<", "Ensure split string, index:9");
	cr_expect_str_eq(result[10], "|", "Ensure split string, index:10");
	cr_expect_str_eq(result[11], "<<", "Ensure split string, index:11");
	ft_matrix_free(result);
}

Test(split_cmd, quote) {
	char	*str = "'ls    -la'";
	char	**result = NULL;

	result = split_cmd(str);
	cr_assert(result, "Ensure split string");
	cr_expect_str_eq(result[0], "'ls    -la'", "Ensure split string, index:0");
	ft_matrix_free(result);
}

Test(split_cmd, quote_in_quote) {
	char	*str = "'\"ls    -la\"'";
	char	**result = NULL;

	result = split_cmd(str);
	cr_assert(result, "Ensure split string");
	cr_expect_str_eq(result[0], "'\"ls    -la\"'", "Ensure split string, index:0");
	ft_matrix_free(result);
}

Test(split_cmd, quote_input_redirect) {
	char	*str = "'ls    -la| >file'";
	char	**result = NULL;

	result = split_cmd(str);
	cr_assert(result, "Ensure split string");
	cr_expect_str_eq(result[0], "'ls    -la| >file'",
		"Ensure split string, index:0");
	ft_matrix_free(result);
}

Test(split_cmd, string_quote) {
	char	*str = "echo   mini's'hell";
	char	**result = NULL;

	result = split_cmd(str);
	cr_assert(result, "Ensure split string");
	cr_expect_str_eq(result[0], "echo", "Ensure split string, index:0");
	cr_expect_str_eq(result[1], "mini's'hell", "Ensure split string, index:1");
	ft_matrix_free(result);
}

Test(split_cmd, string_quote_space) {
	char	*str = "echo   mini's'hell \"ls -la \" pwd";
	char	**result = NULL;

	result = split_cmd(str);
	cr_assert(result, "Ensure split string");
	cr_expect_str_eq(result[0], "echo", "Ensure split string, index:0");
	cr_expect_str_eq(result[1], "mini's'hell", "Ensure split string, index:1");
	cr_expect_str_eq(result[2], "\"ls -la \"", "Ensure split string, index:2");
	cr_expect_str_eq(result[3], "pwd", "Ensure split string, index:3");
	ft_matrix_free(result);
}

Test(split_cmd, string_quote_trunc) {
	char	*str = "echo   mini's'hell>outfile";
	char	**result = NULL;

	result = split_cmd(str);
	cr_expect_str_eq(result[0], "echo", "Ensure split string, index:0");
	cr_expect_str_eq(result[1], "mini's'hell", "Ensure split string, index:1");
	cr_expect_str_eq(result[2], ">", "Ensure split string, index:2");
	cr_expect_str_eq(result[3], "outfile", "Ensure split string, index:3");
	ft_matrix_free(result);
}

Test(split_cmd, string_quote_input) {
	char	*str = "echo   mini's'hell<file";
	char	**result = NULL;

	result = split_cmd(str);
	cr_assert(result, "Ensure split string");
	cr_expect_str_eq(result[0], "echo", "Ensure split string, index:0");
	cr_expect_str_eq(result[1], "mini's'hell", "Ensure split string, index:1");
	cr_expect_str_eq(result[2], "<", "Ensure split string, index:2");
	cr_expect_str_eq(result[3], "file", "Ensure split string, index:3");
	ft_matrix_free(result);
}

Test(split_cmd, string_quote_append) {
	char	*str = "echo   mini's'hell>>file";
	char	**result = NULL;

	result = split_cmd(str);
	cr_assert(result, "Ensure split string");
	cr_expect_str_eq(result[0], "echo", "Ensure split string, index:0");
	cr_expect_str_eq(result[1], "mini's'hell", "Ensure split string, index:1");
	cr_expect_str_eq(result[2], ">>", "Ensure split string, index:2");
	cr_expect_str_eq(result[3], "file", "Ensure split string, index:3");
	ft_matrix_free(result);
}

Test(split_cmd, string_quote_heredoc) {
	char	*str = "echo   mini's'hell<<file";
	char	**result = NULL;

	result = split_cmd(str);
	cr_assert(result, "Ensure split string");
	cr_expect_str_eq(result[0], "echo", "Ensure split string, index:0");
	cr_expect_str_eq(result[1], "mini's'hell", "Ensure split string, index:1");
	cr_expect_str_eq(result[2], "<<", "Ensure split string, index:2");
	cr_expect_str_eq(result[3], "file", "Ensure split string, index:3");
	ft_matrix_free(result);
}

Test(split_cmd, string_quote_pipe) {
	char	*str = "echo   mini's'hell|ls|cat";
	char	**result = NULL;

	result = split_cmd(str);
	cr_assert(result, "Ensure split string");
	cr_expect_str_eq(result[0], "echo", "Ensure split string, index:0");
	cr_expect_str_eq(result[1], "mini's'hell", "Ensure split string, index:1");
	cr_expect_str_eq(result[2], "|", "Ensure split string, index:2");
	cr_expect_str_eq(result[3], "ls", "Ensure split string, index:3");
	cr_expect_str_eq(result[4], "|", "Ensure split string, index:4");
	cr_expect_str_eq(result[5], "cat", "Ensure split string, index:5");
	ft_matrix_free(result);
}

Test(split_cmd, quote_pipe) {
	char	*str = "ls '|' cat";
	char	**result = NULL;

	result = split_cmd(str);
	cr_assert(result, "Ensure split string");
	cr_expect_str_eq(result[0], "ls", "Ensure split string, index:0");
	cr_expect_str_eq(result[1], "'|'", "Ensure split string, index:1");
	cr_expect_str_eq(result[2], "cat", "Ensure split string, index:2");
	ft_matrix_free(result);
}

Test(split_cmd, skip_space_1) {
	char	*str = "                ";
	char	**result = NULL;

	result = split_cmd(str);
	cr_expect(result == NULL, "Ensure returns NULL if string is empty");
}

Test(split_cmd, skip_space_2) {
	char	*str = "                ls      ";
	char	**result = NULL;

	result = split_cmd(str);
	cr_assert(result, "Ensure split string");
	cr_expect_str_eq(result[0], "ls", "Ensure split string, index:0");
	ft_matrix_free(result);
}
