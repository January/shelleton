#include "command.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

CommandHolder make_command_holder(char* redirect_in, char* redirect_out, char flags, Command cmd)
{
  return (CommandHolder)
  {
    redirect_in,
    redirect_out,
    flags,
    cmd
  };
}

Command make_generic_command(char** args)
{
  Command cmd;

  cmd.generic = (GenericCommand)
  {
    GENERIC,
    args
  };

  return cmd;
}

Command make_echo_command(char** strs)
{
  Command cmd;

  cmd.generic = (GenericCommand)
  {
    ECHO,
    strs
  };

  return cmd;
}

Command make_export_command(char* env_var, char* val)
{
  Command cmd;

  cmd.export = (ExportCommand)
  {
    EXPORT,
    env_var,
    val
  };

  return cmd;
}

Command make_cd_command(char* dir)
{
  Command cmd;

  cmd.cd = (CDCommand)
  {
    CD,
    dir
  };

  return cmd;
}

Command make_kill_command(char* sig, char* job)
{
  Command cmd;

  cmd.kill = (KillCommand)
  {
    KILL,
    strtol(sig, NULL, 10),
    strtol(job, NULL, 10),
    sig,
    job
  };

  return cmd;
}

Command make_pwd_command()
{
  Command cmd;

  cmd.pwd = (PWDCommand)
  {
    PWD
  };

  return cmd;
}

Command make_jobs_command()
{
  Command cmd;

  cmd.jobs = (JobsCommand)
  {
    JOBS
  };

  return cmd;
}

Command make_exit_command()
{
  Command cmd;

  cmd.exit = (ExitCommand)
  {
    EXIT
  };

  return cmd;
}

Command make_eoc()
{
  Command cmd;

  cmd.eoc = (EOCCommand)
  {
    EOC
  };

  return cmd;
}


CommandType get_command_type(Command cmd)
{
  return cmd.simple.type;
}

CommandType get_command_holder_type(CommandHolder holder)
{
  return get_command_type(holder.cmd);
}