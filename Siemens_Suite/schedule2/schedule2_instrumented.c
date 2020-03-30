
/* $Log: schedule.c,v $
 * Revision 1.4  1993/05/04  12:23:58  foster
 * Debug stuff removed
 *
 * Revision 1.3  1993/05/03  20:27:04  foster
 * Full Functionality
 *
 * Revision 1.2  1993/05/03  15:41:01  foster
 * Restructure functions
 *
 * Revision 1.1  1993/05/01  11:38:04  foster
 * Initial revision
 * */

#include <stdio.h>
#include "schedule2.h"

/* instrumentation */
 #define _i_function(VAR)     char _v_par1[50], _v_par2[50], _v_par3[50], _v_temp[50], _v_scope[50], _v_function[50] = VAR
 #define _i_node(NODE)        (printf( "node %s.%s\n", _v_function, NODE),NODE)
 #define _i_def(DATA,...)     (sprintf(_v_temp,"%s %s %s",__VA_ARGS__,__VA_ARGS__,__VA_ARGS__),sscanf(_v_temp,"%s %s %s", _v_par1, _v_par2, _v_par3),printf( "def %s.%s %s.%s\n", (strcmp(_v_par1,_v_par3)?_v_par3:_v_function), _v_par1, _v_function, _v_par2),DATA)
 #define _i_cuse(DATA,...)    (sprintf(_v_temp,"%s %s %s",__VA_ARGS__,__VA_ARGS__,__VA_ARGS__),sscanf(_v_temp,"%s %s %s", _v_par1, _v_par2, _v_par3),printf( "c_use %s.%s %s.%s\n", (strcmp(_v_par1,_v_par3)?_v_par3:_v_function), _v_par1, _v_function, _v_par2), DATA)
 #define _i_puse(DATA,...)    (sprintf(_v_temp,"%s %s %s",__VA_ARGS__,__VA_ARGS__,__VA_ARGS__),sscanf(_v_temp,"%s %s %s", _v_par1, _v_par2, _v_par3),printf( "p_use %s.%s %s\n", (strcmp(_v_par1,_v_par2)?_v_par2:_v_function), _v_par1, _v_function), DATA)
 #define _i_loc(NODE1,NODE2)  (printf( "loc %s.%s-%s.%s %s\n", _v_function, NODE1, _v_function, NODE2, _v_function))
 #define _i_scope(LINE)       (sprintf(_v_scope,"%s_%s",_v_function,LINE),_v_scope)

// #define _i_function(VAR)     char _v_par1[50], _v_par2[50], _v_par3[50], _v_temp[50], _v_scope[50], _v_function[50] = VAR
// #define _i_node(NODE)        (NODE)
// #define _i_def(DATA,...)     (sprintf(_v_temp,"%s %s %s",__VA_ARGS__,__VA_ARGS__,__VA_ARGS__),sscanf(_v_temp,"%s %s %s", _v_par1, _v_par2, _v_par3),DATA)
// #define _i_cuse(DATA,...)    (sprintf(_v_temp,"%s %s %s",__VA_ARGS__,__VA_ARGS__,__VA_ARGS__),sscanf(_v_temp,"%s %s %s", _v_par1, _v_par2, _v_par3), DATA)
// #define _i_puse(DATA,...)    (sprintf(_v_temp,"%s %s %s",__VA_ARGS__,__VA_ARGS__,__VA_ARGS__),sscanf(_v_temp,"%s %s %s", _v_par1, _v_par2, _v_par3), DATA)
// #define _i_loc(NODE1,NODE2)  (NODE1)
// #define _i_scope(LINE)       (sprintf(_v_scope,"%s_%s",_v_function,LINE),_v_scope)
/* --------------- */

static struct process * current_job;
static int next_pid = 0;


void global_sets(){
  _i_function("global");
  _i_node("0");
  _i_def(MAXPRIO , "MAXPRIO", "0");
  _i_def(MAXLOPRIO , "MAXLOPRIO", "0");
  _i_def(BLOCKPRIO , "BLOCKPRIO", "0");
  _i_def(CMDSIZE , "CMDSIZE", "0");

  _i_def(NEW_JOB , "NEW_JOB", "0");
  _i_def(UPGRADE_PRIO , "UPGRADE_PRIO", "0");
  _i_def(BLOCK , "BLOCK", "0");
  _i_def(UNBLOCK , "UNBLOCK", "0");
  _i_def(QUANTUM_EXPIRE , "QUANTUM_EXPIRE", "0");
  _i_def(FINISH , "FINISH", "0");
  _i_def(FLUSH , "FLUSH", "0");

  _i_def(OK , "OK", "0");
  _i_def(TRUE , "TRUE", "0");
  _i_def(FALSE , "FALSE", "0");
  _i_def(BADNOARGS , "BADNOARGS", "0");
  _i_def(BADARG , "BADARG", "0");
  _i_def(MALLOC_ERR , "MALLOC_ERR", "0");
  _i_def(BADPRIO , "BADPRIO", "0");
  _i_def(BADRATIO , "BADRATIO", "0");
  _i_def(NO_COMMAND , "NO_COMMAND", "0");
  _i_cuse(MAXPRIO , "MAXPRIO", "0");
  _i_def(1 , "prio_queue", "0");
  _i_def(current_job , "current_job", "0");
  _i_def(next_pid , "next_pid", "0");


}

int
enqueue(prio, new_process)
     int prio;
     struct process *new_process;
{
  _i_function("enqueue");
  _i_node("0");
  _i_def(prio , "prio", "0");
  _i_def(new_process , "new_process", "0");
  _i_node("1");
    int status;
    _i_def(status , "status", "1");
    if(_i_node("2")&&(_i_puse(_i_def( status = put_end(_i_cuse(prio , "prio", "2"), _i_cuse(new_process , "new_process", "2")), "status", "2") , "status"))){
      _i_loc("2", "3");
      _i_node("3");
      return(_i_cuse(status , "status", "3")); /* Error */
    }else{
      _i_loc("2", "4");
      _i_node("4");

    }
    _i_node("5");
    return(reschedule(_i_cuse(prio , "prio", "5")));
}

struct queue
{
    int length;
    struct process *head;
};

static struct queue prio_queue[MAXPRIO + 1]; /* blocked queue is [0] */



main(argc, argv) /* n3, n2, n1 : # of processes at prio3 ... */
int argc;
char *argv[];
{
  global_sets();
  _i_function("main");
  _i_node("0");
  _i_def(argc , "argc", "0");
  _i_def(argv , "argv", "0");
  _i_node("1");
    int command, prio;
    float ratio;
    int nprocs, status, pid;
    struct process *process;
    _i_def(command , "command", "1");
    _i_def(prio , "prio", "1");
    _i_def(ratio , "ratio", "1");
    _i_def(nprocs , "nprocs", "1");
    _i_def(status , "status", "1");
    _i_def(pid , "pid", "1");
    _i_def(process , "process", "1");

    if(_i_node("2") && (_i_puse(argc , "argc") != _i_puse(MAXPRIO , "MAXPRIO","global") + 1)){
      _i_loc("2", "3");
      _i_node("3");
      exit_here(_i_cuse(BADNOARGS , "BADNOARGS", "3","global"));
    }else{
      _i_loc("2", "4");
      _i_node("4");
    }

    for(_i_node("5"),prio = _i_cuse(MAXPRIO , "MAXPRIO", "5","global"),_i_def(prio , "prio", "5");_i_node("6") && (_i_puse(prio , "prio") > 0);_i_node("17") ,_i_def(_i_cuse(prio-- , "prio", "17") , "prio", "17"))
    {
      _i_loc("6", "7");

    	if(_i_node("7")&& _i_puse(_i_def(nprocs=atoi(_i_puse(argv[_i_cuse(MAXPRIO , "MAXPRIO", "7","global") +1 - _i_cuse(prio , "prio", "7")] , "argv")) , "nprocs", "7") < 0, "nprocs")){


        _i_loc("7", "8");
        _i_node("8");
        exit_here(_i_cuse(BADARG , "BADARG", "8","global"));
      }else{
        _i_loc("7", "9");
        _i_node("9");
      }
    	for(_i_node("10");_i_node("11")&& (_i_puse(nprocs , "nprocs") > 0);_i_node("15"),_i_def(_i_cuse(nprocs-- , "nprocs", "15") , "nprocs", "15"))
    	{
        _i_loc("11", "12");

    	    if(_i_node("12") && (_i_puse(_i_def(status  = new_job(_i_puse(prio , "prio")), "status", "12") , "status"))){
            _i_loc("12", "13");
            _i_node("13");
            exit_here(_i_cuse(status , "status", "13"));
          }
          else{
            _i_loc("12", "14");
            _i_node("14");
          }
    	}
      _i_loc("11", "16");
      _i_node("16");
    }
    _i_loc("6", "18");
    /* while there are commands, schedule it */
    while(_i_node("18") && ((_i_puse(_i_def( status  = get_command(_i_cuse(&command , "command", "18"), _i_cuse(&prio , "prio", "18"), _i_cuse(&ratio , "ratio", "18")) > 0, "status", "18"), "status"))))
    {
      _i_loc("18", "19");
      _i_node("19");
	     schedule(_i_cuse( command, "command", "19"), _i_cuse( prio, "prio", "19"), _i_cuse(ratio , "ratio", "19"));
    }
    _i_loc("18", "20");

    if(_i_node("20") && (_i_puse(status , "status") < 0)){
      _i_loc("20", "21");
      _i_node("21");
       exit_here(_i_cuse(status , "status", "22")); /* Real bad error */
    }else{
      _i_loc("20", "22");
      _i_node("22");
    }
    _i_node("23");
    exit_here(_i_cuse(OK , "OK", "23","global"));
}

int
get_command(command, prio, ratio)
    int *command, *prio;
    float *ratio;
{
  _i_function("get_command");
  _i_node("0");
  _i_def(command , "command", "0");
  _i_def(prio , "prio", "0");
  _i_def(ratio , "ratio", "0");
  _i_node("1");
    int status = _i_cuse(OK , "OK", "1","global");
    _i_def(status , "status", "1");

    _i_node("2");
    char buf[_i_cuse(CMDSIZE , "CMDSIZE", "2","global")];
    _i_def(buf , "buf", "2");

    if(_i_node("3") && (_i_def( fgets(buf, _i_cuse(CMDSIZE , "CMDSIZE", "3","global"), stdin), "buf", "3")))
    {
      _i_loc("3", "4");
      _i_node("4");

      	*prio = _i_cuse( _i_def(*command  = -1, "command", "4"), "command", "4");
        _i_def(prio , "prio", "4");
        _i_node("5");
         *ratio =-1.0;
         _i_def(ratio , "ratio", "5");
         _i_node("6");
      	sscanf(_i_cuse(buf , "buf", "6"), "%d", _i_def( _i_cuse(command , "command", "6"), "command", "6"));


      	switch(*command)
      	{
      	  case NEW_JOB :
          _i_node("7");
          _i_puse(command , "command");
          _i_puse(NEW_JOB , "NEW_JOB","global");
          _i_loc("7", "8");
          _i_node("8");

      	    sscanf(_i_cuse(buf , "buf", "8"), "%*s%d", _i_def(_i_cuse(prio , "prio", "8") , "prio", "8"));
      	    break;
      	  case UNBLOCK :
            _i_node("7");
            _i_puse(command , "command");
            _i_puse(UNBLOCK , "UNBLOCK");
            _i_loc("7", "9");
            _i_node("9");
      	    sscanf(_i_cuse(buf , "buf", "9"), "%*s%f", _i_def( _i_cuse(ratio, "ratio", "9"), "ratio", "9"));
      	    break;
      	  case UPGRADE_PRIO :
            _i_node("7");
            _i_puse(command , "command");
            _i_puse(UPGRADE_PRIO , "UPGRADE_PRIO","global");
            _i_loc("7", "10");
            _i_node("10");
      	    sscanf(_i_cuse(buf , "buf", "10"), "%*s%d%f", _i_def(_i_cuse(prio , "prio", "10") , "prio", "10"), _i_def( _i_cuse(ratio , "ratio", "10"), "ratio", "10"));
      	    break;
      	}

      	 /* Find end of  line of input if no EOF */
      	while(_i_node("11") && (_i_puse(buf[strlen(_i_cuse(buf , "buf", "11"))-1] , "buf") != '\n' && _i_puse( _i_def( fgets(buf, _i_cuse(CMDSIZE , "CMDSIZE", "11","global"), stdin), "buf", "11"), "buf"))){
          _i_loc("11", "11A");
          _i_node("11A");
        }
        _i_loc("11A", "12");
        _i_node("12");
        return(_i_cuse(TRUE , "TRUE", "12","global"));
    }
    else{
      _i_loc("3", "13");
      _i_node("13");
       return(_i_cuse(FALSE , "FALSE", "13","global"));
    }
}

exit_here(status)
     int status;
{
  _i_function("exit_here");
  _i_node("0");
  _i_def(status , "status", "0");
  _i_node("1");
    exit(abs(_i_cuse(status , "status", "1")));
}


int
new_job(prio) /* allocate new pid and process block. Stick at end */
     int prio;
{
  _i_function("new_job");
  _i_node("0");
  _i_def(prio , "prio", "0");
  _i_node("1");
    int pid;
    _i_def(pid , "pid", "1");

    _i_node("2");
    int status = _i_cuse(OK , "OK", "2","global");
    _i_def(status , "status", "2");
    _i_node("3");
    struct process *new_process;
    _i_def(new_process , "new_process", "3");
    _i_node("4");
    pid = _i_def(_i_cuse(next_pid++ , "next_pid", "4","global") , "next_pid", "4","global");
    _i_def(pid , "pid", "4");
    _i_node("5");
    new_process = (struct process *) malloc(sizeof(struct process));
    _i_def(new_process , "new_process", "5");
        if(_i_node("6") && (!_i_puse(new_process , "new_process"))){
          _i_loc("6", "7");
          _i_node("7");
           status = _i_cuse(MALLOC_ERR , "MALLOC_ERR", "7","global");
           _i_def(status , "status", "7");
        }
    else
    {_i_loc("6", "8");
    _i_node("8");
    	new_process->pid = _i_cuse(pid , "pid", "8");
      _i_def(new_process , "new_process", "8");
      _i_node("9");
    	new_process->priority = _i_cuse(prio , "prio", "9");
      _i_def(new_process , "new_process", "9");
      _i_node("10");
    	new_process->next = (struct process *) 0;
      _i_def(new_process , "new_process", "10");
      _i_node("11");
    	status = enqueue(_i_cuse(prio , "prio", "11"), _i_cuse(new_process , "new_process", "11"));
      _i_def(status , "status", "11");
    	if(_i_node("12") && (status))
    	{
          _i_loc("12", "13");
          _i_node("13");
    	    free(_i_cuse(new_process , "new_process", "13")); /* Return process block */
    	}else{
        _i_loc("12", "14");
        _i_node("14");
      }
    }
    if(_i_node("15") && (_i_cuse(status , "status", "15"))){
      _i_loc("15", "16");
      _i_node("16");
      _i_def(_i_cuse(next_pid-- , "next_pid", "16","global") , "next_pid", "16","global");
       /* Unsuccess. Restore pid */
    }else{
      _i_loc("15", "17");
      _i_node("17");

    }
    _i_node("18");
    return(_i_cuse(status , "status", "18"));
}

int upgrade_prio(prio, ratio) /* increment priority at ratio in queue */
     int prio;
     float ratio;
{
  _i_function("upgrade_prio");
  _i_node("0");
  _i_def(prio , "prio", "0");
  _i_def(ratio , "ratio", "0");
  _i_node("1");
    int status;
    _i_def(status , "status", "1");
    struct process * job;

    if(_i_node("2") && (_i_puse(prio , "prio") < 1 || _i_puse(prio , "prio") > _i_puse(MAXLOPRIO , "MAXLOPRIO","global"))){
      _i_loc("2", "3");
      _i_node("3");
       return(_i_cuse(BADPRIO , "BADPRIO", "3","global"));
    }else{
      _i_loc("2", "4");
      _i_node("4");
    }

    if(_i_node("5") && ((_i_puse( _i_def( status = get_process(_i_cuse(prio , "prio", "5"), _i_cuse(ratio , "ratio", "5"), _i_cuse(&job , "&job", "5"))<= 0, "status", "6"), "status")))){
      _i_loc("5", "6");
      _i_node("6");
       return(_i_cuse(status , "status", "6"));
    }else{
      _i_loc("5", "7");
      _i_node("7");
    }
    _i_node("8");
    /* We found a job in that queue. Upgrade it */
    job->priority = _i_cuse(prio , "prio", "8") + 1;
    _i_def(job , "job", "8");
    _i_node("8");
    return(enqueue(_i_cuse(prio , "prio", "8") + 1, _i_cuse(job , "job", "8")));
}

int
block() /* Put current job in blocked queue */
{
  _i_function("block");
  _i_node("0");
  _i_node("1");
    struct process * job;
    _i_def(job , "job", "1");
    _i_node("2");
    job = get_current();
    _i_def(job , "job", "2");
    if(_i_node("3") && (_i_puse(job , "job")))
    {
      _i_loc("3", "4");
      _i_node("4");
    	current_job = (struct process *)0; /* remove it */
      _i_def(current_job , "current_job", "4","global");
      _i_node("5");
    	return(enqueue(_i_cuse(BLOCKPRIO , "BLOCKPRIO", "5","global"), _i_cuse(job , "job", "5"))); /* put into blocked queue */
    }else{
      _i_loc("3", "6");
      _i_node("6");

    }
    _i_node("7");
    return(_i_cuse(OK , "OK", "7","global"));
}

int
unblock(ratio) /* Restore job @ ratio in blocked queue to its queue */
     float ratio;
{
  _i_function("unblock");
  _i_node("0");
  _i_def(ratio , "ratio", "0");
  _i_node("1");
    int status;
    struct process * job;
    _i_def(status , "status", "1");
    _i_def(job , "job", "1");
    if(_i_node("2") && (_i_puse(_i_def(status = get_process(_i_cuse(BLOCKPRIO , "BLOCKPRIO", "2","global"), _i_cuse(ratio , "ratio", "2"), _i_cuse(&job , "job", "2")) <= 0, "status", "2"), "status"))){
      _i_loc("2", "3");
      _i_node("3");
      return(_i_cuse(status , "status", "3"));
    }else{
      _i_loc("2", "4");
      _i_node("4");
    }
    /* We found a blocked process. Put it where it belongs. */
    _i_node("5");
    return(enqueue(_i_cuse(job->priority , "job", "5"), _i_cuse(job , "job", "5")));
}

int
quantum_expire() /* put current job at end of its queue */
{
  _i_function("quantum_expire");
  _i_node("0");
  _i_node("1");
    struct process * job;
    _i_def(job , "job", "1");
    _i_node("2");
    job = get_current();
    _i_def(job , "job", "3");
    if(_i_node("4")&&(_i_puse(job , "job")))
    {
      _i_loc("4", "5");
      _i_node("5");
      	current_job = (struct process *)0; /* remove it */
        _i_def(current_job , "current_job", "5","global");
        _i_node("6");
      	return(enqueue(_i_cuse(job->priority , "job", "6"), _i_cuse(job , "job", "6")));
    }else{
      _i_loc("4", "7");
      _i_node("7");
    }
    _i_node("8");
    return(_i_cuse(OK , "OK", "8","global"));
}

int
finish() /* Get current job, print it, and zap it. */
{
  _i_function("finish");
  _i_node("0");
  _i_node("1");
    struct process * job;
    _i_def(job , "job", "1");
    _i_node("2");
    job = get_current();
    _i_def(job , "job", "2");

    if(_i_node("3")&&(_i_puse(job , "job")))
    {_i_loc("3", "4");
    _i_node("4");
    	current_job = (struct process *)0;
      _i_def(current_job , "current_job", "4","global");
      _i_node("5");
    	reschedule(0);
      _i_node("6");
    	fprintf(stdout, " %d", _i_def(_i_cuse(job->pid , "job", "6") , "job", "6"));
      _i_node("7");
    	free(_i_cuse(job , "job", "7"));
      _i_node("8");
    	return(_i_cuse(FALSE , "FALSE", "8","global"));
    }
    else{
      _i_loc("3", "9");
      _i_node("9");
       return(_i_cuse(TRUE , "TRUE", "9","global"));
    }
}

int
flush() /* Get all jobs in priority queues & zap them */
{
  _i_function("flush");
  _i_node("0");

    while(_i_node("1")&&(!finish())){
      _i_loc("1", "2");
      _i_node("2");
    }
    _i_loc("1", "3");
    _i_node("3");
    fprintf(stdout, "\n");
    _i_node("4");
    return(_i_cuse(OK , "OK", "4","global"));
}

struct process *
get_current() /* If no current process, get it. Return it */
{
  _i_function("get_current");
  _i_node("0");
  _i_node("1");
    int prio;
    _i_def(prio , "prio", "1");
    if(_i_node("2") && (!_i_puse(current_job , "current_job","global")))
    {
      _i_loc("2", "3");

      	for(_i_node("3"),prio = _i_cuse(MAXPRIO , "MAXPRIO", "3","global"),_i_def(prio , "prio", "3");_i_node("4")&&(_i_puse(prio , "prio") > 0);_i_node("8"),_i_def(_i_cuse(prio-- , "prio", "8") , "prio", "8") )
      	{ /* find head of highest queue with a process */
          _i_loc("4", "5");

      	    if(_i_node("5")&& (get_process(_i_cuse(prio , "prio", "5"), 0.0, _i_cuse(&current_job , "current_job", "5","global")) > 0)){
              _i_loc("5", "6");
              _i_node("6");
              break;
            }
            else{
              _i_loc("5", "7");
              _i_node("7");
            }
      	}
        _i_loc("4", "9");
        _i_node("9");
    }else{
      _i_loc("2", "10");
      _i_node("10");
    }
    _i_node("11");
    return(_i_cuse(current_job , "current_job", "10","global"));
}

int
reschedule(prio) /* Put highest priority job into current_job */
     int prio;
{
  _i_function("reschedule");
  _i_node("0");
  _i_def(prio , "prio", "0");

    if(_i_node("1") && (_i_puse(current_job , "current_job","global") && _i_puse(prio , "prio") >_i_puse(current_job->priority , "current_job","global")))
    {
      _i_loc("1", "2");
      _i_node("2");
    	put_end(_i_cuse(current_job->priority , "current_job", "2","global"), _i_cuse(current_job , "current_job", "2","global"));
      _i_node("3");
    	current_job = (struct process *)0;
      _i_def(current_job , "current_job", "3","global");
    }else{
      _i_loc("1", "4");
      _i_node("4");
    }
    _i_node("5");
    get_current(); /* Reschedule */
    _i_node("6");
    return(_i_cuse(OK , "OK", "6","global"));
}

int
schedule(command, prio, ratio)
    int command, prio;
    float ratio;
{
  _i_function("schedule");
  _i_node("0");
  _i_def(command , "command", "0");
  _i_def(prio , "prio", "0");
  _i_def(ratio , "ratio", "0");
  _i_node("1");
    int status = _i_cuse(OK , "OK", "1","global");
    _i_def(status , "status", "1");

    switch(command)
    {
      case NEW_JOB :
      _i_node("2");
      _i_puse(command , "command");
      _i_puse(NEW_JOB , "NEW_JOB","global");
      _i_loc("2", "3");
      _i_node("3");
        status = new_job(_i_cuse(prio , "prio", "3"));
        _i_def(status , "status", "3");
	       break;
      case QUANTUM_EXPIRE :
      _i_node("2");
      _i_puse(command , "command");
      _i_puse(QUANTUM_EXPIRE , "QUANTUM_EXPIRE","global");
      _i_loc("2", "4");
      _i_node("5");
        status = quantum_expire();
        _i_def(status , "status", "5");
	      break;
      case UPGRADE_PRIO :
      _i_node("2");
      _i_puse(command , "command");
      _i_puse(UPGRADE_PRIO , "UPGRADE_PRIO","global");
      _i_loc("2", "6");
      _i_node("6");
        status = upgrade_prio(_i_cuse(prio , "prio", "6"), _i_cuse(ratio , "ratio", "6"));
        _i_def(status , "status", "6");
	      break;
      case BLOCK :
      _i_node("2");
      _i_puse(command , "command");
      _i_puse(BLOCK , "BLOCK","global");
      _i_loc("2", "7");
      _i_node("7");
        status = block();
        _i_def(status , "status", "7");
	break;
      case UNBLOCK :
      _i_node("2");
      _i_puse(command , "command");
      _i_puse(UNBLOCK , "UNBLOCK");
      _i_loc("2", "8");
      _i_node("8");
        status = unblock(_i_cuse(ratio , "ratio", "8"));
        _i_def(status , "status", "8");
	break;
      case FINISH :
      _i_node("2");
      _i_puse(command , "command");
      _i_puse(FINISH , "FINISH","global");
      _i_loc("2", "9");
      _i_node("9");
      finish();
      _i_node("10");
    	fprintf(stdout, "\n");
    	break;
      case FLUSH :
        _i_node("2");
        _i_puse(command , "command");
        _i_puse(FLUSH , "FLUSH","global");
        _i_loc("2", "11");
        _i_node("11");
        status = flush();
        _i_def(status , "status", "11");
	    break;
      default:
      _i_node("2");
      _i_puse(command , "command");
      _i_loc("2", "12");
      _i_node("12");
	     status = _i_cuse(NO_COMMAND , "NO_COMMAND", "12","global");
       _i_def(status , "status", "12");
    }
    _i_node("13");
    return(_i_cuse(status , "status", "13"));
}




int
put_end(prio, process) /* Put process at end of queue */
     int prio;
     struct process *process;
{
    _i_function("put_end");
    _i_node("0");
    _i_def(prio , "prio", "0");
    _i_def(process , "process", "0");
    _i_node("1");
    struct process **next;
    _i_def(next , "next", "1");
    if(_i_node("2") && (_i_puse(prio , "prio") > _i_puse(MAXPRIO , "MAXPRIO","global") || _i_puse(prio , "prio") < 0)){
      _i_loc("2", "3");
      _i_node("3");
      return(_i_cuse(BADPRIO , "BADPRIO", "3","global")); /* Somebody goofed */
    }else{
      _i_loc("2", "4");
      _i_node("4");

    }

     /* find end of queue */
    for(_i_node("5"), next = _i_cuse(&prio_queue[_i_cuse(prio , "prio", "5")].head , "prio_queue", "5","global"),_i_def(next , "next", "5");_i_node("6")&& (*next);_i_node("8"), next = _i_cuse(&(*next)->next , "next", "8"),_i_def(next , "next", "8")){
      _i_loc("6", "7");
      _i_node("7");
    }
    _i_loc("6", "9");
    _i_node("9");
    *next = _i_cuse(process , "process", "9");
    _i_def(next , "next", "9");
    _i_node("10");
     _i_def(_i_cuse(prio_queue[_i_cuse(prio , "prio", "10")].length++ , "prio_queue", "10","global") , "prio_queue", "10","global");
    _i_node("11");
    return(_i_cuse(OK , "OK", "11","global"));
}

int
get_process(prio, ratio, job)
     int prio;
     float ratio;
     struct process ** job;
{
  _i_function("get_process");
  _i_node("0");
  _i_def(prio , "prio", "0");
  _i_def(ratio , "ratio", "0");
  _i_def(job , "job", "0");
  _i_node("1");
    int length, index;
    struct process **next;
    _i_def(length , "length", "1");
    _i_def(index , "index", "1");
    _i_def(next , "next", "1");

    if(_i_node("2") && (_i_puse(prio , "prio") > _i_puse(MAXPRIO , "MAXPRIO","global") || _i_puse(prio , "prio") < 0)){
      _i_loc("2", "3");
      _i_node("3");
       return(_i_cuse(BADPRIO , "BADPRIO", "3","global")); /* Somebody goofed */
    }else{
      _i_loc("2", "4");
      _i_node("4");
    }

    if(_i_node("5") && (_i_puse(ratio , "ratio") < 0.0 || _i_puse(ratio , "ratio") > 1.0)){
      _i_loc("5", "6");
      _i_node("6");
       return(_i_cuse(BADRATIO , "BADRATIO", "6","global")); /* Somebody else goofed */
    }else{
      _i_loc("5", "7");
      _i_node("7");
    }
    _i_node("8");
    length = _i_cuse(prio_queue[_i_cuse(prio , "prio", "8")].length , "prio_queue", "8","global");
    _i_def(length , "length", "8");
    _i_node("9");
    index = _i_cuse(ratio , "ratio", "9") * _i_cuse(length , "length", "9");
    _i_def(index , "index", "9");

    if(_i_node("10") && (_i_puse(index , "index") >= _i_puse(length , "length"))){
      _i_loc("10", "11");
      _i_node("11");
        index = _i_cuse(length , "length", "11") -1;
        _i_def(index , "index", "11");
    }else{
      _i_loc("10", "12");
      _i_node("12");
      index =_i_cuse(index , "index", "12");
      _i_def(index , "index", "12");
    }

    for(_i_node("13"), next = _i_cuse(&prio_queue[_i_cuse(prio , "prio", "13")].head , "prio_queue", "13","global"),_i_def(next , "next", "13");_i_node("14") && (_i_puse(index , "index") && _i_puse(*next , "next"));_i_node("16"), _i_def(_i_cuse(index-- , "index", "16") , "index", "16") ){
      _i_loc("14", "15");
      _i_node("15");
        next = _i_cuse(&(*next)->next , "next", "15"); /* Count up to it */
        _i_node("next");
    }
    _i_node("17");
    *job = _i_cuse(*next , "next", "17");
    _i_def(job , "job", "17");

    if(_i_node("18")&&(_i_puse(*job , "job")))
    {
      _i_loc("18", "19");
      _i_node("19");
    	*next = _i_cuse((*next)->next , "next", "19"); /* Mend the chain */
      _i_def(next , "next", "19");
      _i_node("20");
    	(*job)->next = (struct process *) 0; /* break this link */
      _i_def(*job , "job", "20");
      _i_node("21");

      _i_def(_i_cuse(prio_queue[_i_cuse(prio , "prio", "21")].length-- , "prio_queue", "21","global") , "prio_queue", "21","global");
      _i_node("22");
      return(_i_cuse(TRUE , "TRUE", "22","global"));
    }
    else{
      _i_loc("18", "23");
      _i_node("23");
       return(_i_cuse(FALSE , "FALSE", "23","global"));
    }
}
