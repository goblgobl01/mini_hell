#include "../header.h"

// int tmp_out = dup(1);
// int tmp_in = dup(0);
// redirect()
// dup2(tmp_out, 1);
// dup2(tmp_in, 0);

void handle_redirection(t_command *cmd, t_env_copy *env)
{
    int i;
    int fd;

    i = 0;

    while (cmd->redirctions[i])
    {
        if (cmd->redirctions[i]->type == IN)
        {
            fd = open(cmd->redirctions[i]->file, O_RDONLY);
            if (fd < 0)
            {
                dprintf(2, "bash: %s: No such file or directory\n", cmd->redirctions[i]->file);
                update_environment(env, "?", "1");
                exit(1);
            }
            dup2(fd, STDIN_FILENO);
            close(fd);
        }
        else if (cmd->redirctions[i]->type == OUT)
        {
            fd = open(cmd->redirctions[i]->file, O_CREAT | O_TRUNC | O_WRONLY, 0644);
            if (fd < 0)
            {
                dprintf(2, "bash: %s: No such file or directory\n", cmd->redirctions[i]->file);
                update_environment(env, "?", "1");
                exit(1);
            }
            dup2(fd, STDOUT_FILENO);
            close(fd);
        }
        else if (cmd->redirctions[i]->type == APPEND)
        {
            fd = open(cmd->redirctions[i]->file, O_CREAT | O_APPEND | O_WRONLY, 0644);
            if (fd < 0)
            {
                dprintf(2, "bash: %s: No such file or directory\n", cmd->redirctions[i]->file);
                update_environment(env, "?", "1");
                exit(1);
            }
            dup2(fd, STDOUT_FILENO);
            close(fd);
        }
        else if (cmd->redirctions[i]->type == HEREDOC)
        {
            int fd_herd;
            fd_herd = cmd->redirctions[i]->fd_heredoc;
            dup2(fd_herd, STDIN_FILENO);
            close(fd_herd);
        }
        i++;
    }
}
