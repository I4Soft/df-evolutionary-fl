/*  -*- Last-Edit:  Wed May 7 10:12:52 1993 by Monica; -*- */


#include <stdio.h>

/* A job descriptor. */
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

#define NULL 0


#define NEW_JOB        1
#define UPGRADE_PRIO   2
#define BLOCK          3
#define UNBLOCK        4
#define QUANTUM_EXPIRE 5
#define FINISH         6
#define FLUSH          7

#define MAXPRIO 3

typedef struct _job {
    struct  _job *next, *prev; /* Next and Previous in job list. */
    int          val  ;         /* Id-value of program. */
    short        priority;     /* Its priority. */
} Ele, *Ele_Ptr;

typedef struct list		/* doubly linked list */
{
  Ele *first;
  Ele *last;
  int    mem_count;		/* member count */
} List;


void global_sets(){
  _i_function("global");
  _i_node("0");
  _i_def(NULL , "NULL", "0");
  _i_def(NEW_JOB , "NEW_JOB", "0");
  _i_def(UPGRADE_PRIO , "UPGRADE_PRIO", "0");
  _i_def(BLOCK , "BLOCK", "0");
  _i_def(UNBLOCK , "UNBLOCK", "0");
  _i_def(QUANTUM_EXPIRE , "QUANTUM_EXPIRE", "0");
  _i_def(FINISH , "FINISH", "0");
  _i_def(FLUSH , "FLUSH", "0");
  _i_def(MAXPRIO , "MAXPRIO", "0");
  _i_def(1, "alloc_proc_num", "0");
  _i_def(1 , "num_processes", "0");
  _i_def(1 , "cur_proc", "0");
  _i_cuse(MAXPRIO , "MAXPRIO", "0");
  _i_def(1 , "prio_queue", "0");
  _i_def(1 , "block_queue", "0");

}
/*-----------------------------------------------------------------------------
  new_ele
     alloates a new element with value as num.
-----------------------------------------------------------------------------*/
Ele* new_ele(new_num)
int new_num;
{
  _i_function("new_ele");
  _i_node("0");
  _i_def(new_num , "new_num", "0");
  _i_node("1");
    Ele *ele;
    ele =(Ele *)malloc(sizeof(Ele));
    _i_def(ele , "ele", "1");
    _i_def(ele , "ele", "1");
    _i_node("1_1");
    ele->next = _i_cuse(NULL , "NULL", "1_1","global");
    _i_def(ele , "ele", "1_1");

    _i_node("1_2");
    ele->prev = _i_cuse(NULL , "NULL", "1_2","global");
    _i_def(ele , "ele", "1_2");

    _i_node("2");
    ele->val  = _i_cuse(new_num , "new_num", "2");
    _i_def(ele , "ele", "2");

    _i_node("3");
    return _i_cuse(ele , "ele", "3");
}

/*-----------------------------------------------------------------------------
  new_list
        allocates, initializes and returns a new list.
        Note that if the argument compare() is provided, this list can be
            made into an ordered list. see insert_ele().
-----------------------------------------------------------------------------*/
List *new_list()
{
  _i_function("new_list");
  _i_node("0");
  _i_node("1");
    List *list;
    list = (List *)malloc(sizeof(List));
    _i_def(list , "list", "1");
    _i_def(list , "list", "1");
    _i_node("2");
    list->first = _i_cuse( NULL, "NULL", "2","global");
    _i_def(list , "list", "2");
    _i_node("3");
    list->last  = _i_cuse(NULL , "NULL", "3","global");
    _i_def(list , "list", "3");
    _i_node("4");
    list->mem_count = 0;
    _i_def(list , "list", "4");
    _i_node("5");
    return (_i_cuse(list , "list", "5"));
}

/*-----------------------------------------------------------------------------
  append_ele
        appends the new_ele to the list. If list is null, a new
	list is created. The modified list is returned.
-----------------------------------------------------------------------------*/
List *append_ele(a_list, a_ele)
List *a_list;
Ele  *a_ele;
{
  _i_function("append_ele");
  _i_node("0");
  _i_def(a_list , "a_list", "0");
  _i_def(a_ele , "a_ele", "0");

  if (_i_node("1") && (!_i_puse(a_list , "a_list"))){
    _i_loc("1", "2");
    _i_node("2");
      a_list = new_list();	/* make list without compare function */
      _i_def(a_list, "a_list", "2");
  }else{
    _i_loc("1", "3");
    _i_node("3");
  }
  _i_node("4");
  a_ele->prev = _i_cuse(a_list->last , "a_list", "4");	/* insert at the tail */
  _i_def(a_ele , "a_ele", "4");

  if (_i_node("5") && (_i_puse(a_list->last , "a_list"))){
    _i_loc("5", "6");
    _i_node("6");
    a_list->last->next = _i_cuse(a_ele , "a_ele", "6");
    _i_def(a_list , "a_list", "6");
  }
  else{
    _i_loc("5", "7");
    _i_node("7");
    a_list->first = _i_cuse(a_ele , "a_ele", "7");
    _i_def(a_list , "a_list", "7");
  }
    _i_node("8");
    a_list->last = _i_cuse(a_ele , "a_ele", "8");
    _i_def(a_list , "a_list", "8");
    _i_node("9");
    a_ele->next = _i_cuse(NULL , "NULL", "9","global");
    _i_def(a_ele , "a_ele", "9");
    _i_def(_i_cuse(a_list->mem_count++ , "a_list", "9") , "a_list", "9");
  _i_node("10");
  return (_i_cuse(a_list , "a_list", "10"));
}

/*-----------------------------------------------------------------------------
  find_nth
        fetches the nth element of the list (count starts at 1)
-----------------------------------------------------------------------------*/
Ele *find_nth(f_list, n)
List *f_list;
int   n;
{
  _i_function("find_nth");
  _i_node("0");
  _i_def(f_list , "f_list", "0");
  _i_def(n , "n", "0");
  _i_node("1");
    Ele *f_ele;
    int i;
    _i_def(f_ele , "f_ele", "1");
    _i_def(i , "i", "1");
    if (_i_node("2") &&(!_i_puse(f_list , "f_list"))){
      _i_loc("2", "3");
      _i_node("3");
	     return _i_cuse(NULL , "NULL", "3","global");
     }else{
       _i_loc("2", "4");
       _i_node("4");
     }
     _i_node("5");
    f_ele = _i_cuse(f_list->first , "f_list", "5");
    _i_def(f_ele , "f_ele", "5");
    for (_i_node("6"),i=1,_i_def(i , "i", "6");_i_node("7")&& (_i_puse(f_ele , "f_ele") && (_i_puse(i , "i")<_i_puse(n , "n")));_i_node("9"),_i_def(_i_cuse(i++ , "i", "9") , "i", "9")){
      _i_loc("7", "8");
      _i_node("8");
	     f_ele = _i_cuse(f_ele->next , "f_ele", "8");
       _i_def(f_ele , "f_ele", "8");
     }
     _i_loc("7", "10");
     _i_node("10");
    return _i_cuse(f_ele , "f_ele", "10");
}

/*-----------------------------------------------------------------------------
  del_ele
        deletes the old_ele from the list.
        Note: even if list becomes empty after deletion, the list
	      node is not deallocated.
-----------------------------------------------------------------------------*/
List *del_ele(d_list, d_ele)
List *d_list;
Ele  *d_ele;
{
  _i_function("del_ele");
  _i_node("0");
  _i_def(d_list , "d_list", "0");
  _i_def(d_ele , "d_ele", "0");
    if (_i_node("1") && (!_i_puse(d_list , "d_list") || !_i_puse(d_ele , "d_ele"))){
      _i_loc("1", "2");
      _i_node("2");
	   return (_i_cuse(NULL , "NULL", "2","global"));
   }else{
     _i_loc("1", "3");
     _i_node("3");
   }

    if (_i_node("4") && (_i_puse(d_ele->next , "d_ele"))){
      _i_loc("4", "5");
      _i_node("5");
	     d_ele->next->prev = _i_cuse(d_ele->prev , "d_ele", "5");
       _i_def(d_ele , "d_ele", "5");
     }
    else{
      _i_loc("4", "6");
      _i_node("6");
	     d_list->last = _i_cuse(d_ele->prev, "d_ele", "6");
       _i_def(d_list , "d_list", "6");
     }

    if (_i_node("7")&&(_i_puse(d_ele->prev , "d_ele"))){
      _i_loc("7", "8");
      _i_node("8");
	     d_ele->prev->next = _i_cuse(d_ele->next , "d_ele", "8");
       _i_def(d_ele , "d_ele", "8");
     }
    else{
      _i_loc("7", "9");
      _i_node("9");
	     d_list->first = _i_cuse(d_ele->next , "d_ele", "9");
       _i_def(d_list , "d_list", "9");
     }
    /* KEEP d_ele's data & pointers intact!! */
    _i_node("10");
    _i_def(_i_cuse(d_list->mem_count-- , "d_list", "10") , "d_list", "10");
    _i_node("11");
    return (_i_cuse(d_list , "d_list", "11"));
}

/*-----------------------------------------------------------------------------
   free_ele
       deallocate the ptr. Caution: The ptr should point to an object
       allocated in a single call to malloc.
-----------------------------------------------------------------------------*/
void free_ele(ptr)
Ele *ptr;
{
  _i_function("free_ele");
  _i_node("0");
  _i_def(ptr , "ptr", "0");
  _i_node("1");
    free(_i_cuse(ptr , "ptr", "1"));
}

int alloc_proc_num;
int num_processes;
Ele* cur_proc;
List *prio_queue[MAXPRIO+1]; 	/* 0th element unused */
List *block_queue;

void
finish_process()
{
  _i_function("finish_process");
  _i_node("0");
  _i_node("1");
    schedule();
    if (_i_node("2")&& (_i_puse(cur_proc , "cur_proc","global"))){
      _i_loc("2", "3");
      _i_node("3");
    	fprintf(stdout, "%d ", _i_cuse(cur_proc->val , "cur_proc", "3","global"));
      _i_node("4");
    	free_ele(_i_cuse(cur_proc , "cur_proc", "4","global"));
      _i_node("5");
      _i_def(_i_cuse(num_processes-- , "num_processes", "5","global") , "num_processes", "5","global");

    }else{
      _i_loc("2", "6");
      _i_node("6");
    }
}

void
finish_all_processes()
{
  _i_function("finish_all_processes");
  _i_node("0");

  _i_node("1");
    int i;
    int total;
    _i_def(i , "i", "1");
    _i_def(total , "total", "1");
    _i_node("2");
    total = _i_cuse(num_processes , "num_processes", "2","global");
    _i_def(total , "total", "2");

    for (_i_node("3"),i=0,_i_def(i , "i", "3");_i_node("4") && (_i_puse(i , "i")<_i_puse(total , "total"));_i_node("6"),_i_def(_i_cuse(i++ , "i", "6") , "i", "6") ){
      _i_loc("4", "5");
      _i_node("5");
	     finish_process();
     }
     _i_loc("4", "7");
     _i_node("7");
}

schedule()
{
  _i_function("schedule");
  _i_node("0");
  _i_node("1");
    int i;
    _i_def(i , "i", "1");
    _i_node("1A");
    cur_proc = _i_cuse(NULL , "NULL", "1A","global");
    _i_def(cur_proc , "cur_proc", "1A","global");
    for (_i_node("2"), i=_i_cuse(MAXPRIO , "MAXPRIO", "2","global"), _i_def(i , "i", "2");_i_node("3") && (_i_puse(i , "i") > 0);_i_node("9"),_i_def(_i_cuse(i-- , "i", "9") , "i", "9") )
    {
      _i_loc("3", "4");
    	if (_i_node("4") && (_i_puse(prio_queue[_i_cuse(i , "i", "4")]->mem_count , "prio_queue","global") > 0))
    	{
        _i_loc("4", "5");
        _i_node("5");
    	    cur_proc = _i_cuse(prio_queue[_i_cuse(i , "i", "5")]->first , "prio_queue", "5","global");
          _i_def(cur_proc , "cur_proc", "5","global");
          _i_node("6");
    	    prio_queue[_i_cuse(i , "i", "6")] = del_ele(_i_cuse(prio_queue[_i_cuse(i , "i", "6")] , "prio_queue", "6","global"), _i_cuse(cur_proc , "cur_proc", "6","global"));
          _i_def(prio_queue , "prio_queue", "6","global");
          _i_node("7");
    	    return;
    	}else{
        _i_loc("4", "8");
        _i_node("8");
      }
    }
    _i_loc("3", "10");
    _i_node("10");

}

void
upgrade_process_prio(prio, ratio)
int prio;
float ratio;
{
    _i_function("upgrade_process_prio");
    _i_node("0");
    _i_def(prio , "prio", "0");
    _i_def(ratio , "ratio", "0");
    _i_node("1");
    int count;
    int n;
    Ele *proc;
    List *src_queue, *dest_queue;

    _i_def(count , "count", "1");
    _i_def(n , "n", "1");
    _i_def(proc , "proc", "1");
    _i_def(src_queue , "src_queue", "1");
    _i_def(dest_queue , "dest_queue", "1");


    if (_i_node("2") && (_i_puse(prio , "prio") >= _i_puse(MAXPRIO , "MAXPRIO","global"))){
      _i_loc("2", "3");
      _i_node("3");
	   return;
   }else{
     _i_loc("2", "4");
     _i_node("4");
   }
   _i_node("5");
    src_queue = _i_cuse(prio_queue[_i_cuse(prio , "prio", "5")] , "prio_queue", "5","global");
    _i_def(src_queue , "src_queue", "5");
    _i_node("6");
    dest_queue = _i_cuse(prio_queue[_i_cuse(prio , "prio", "6")+1] , "prio_queue", "6","global");
    _i_def(dest_queue , "dest_queue", "6");
    _i_node("7");
    count = _i_cuse(src_queue->mem_count , "src_queue", "7");
    _i_def(count , "count", "7");

    if (_i_node("8") && (_i_puse(count , "count") > 0))
    {
      _i_loc("8", "9");
      _i_node("9");
      	n = (int) (_i_cuse(count , "count", "9")*_i_cuse(ratio , "ratio", "9") + 1);
        _i_def(n , "n", "9");
        _i_node("10");
      	proc = find_nth(_i_cuse(src_queue , "src_queue", "10"), _i_cuse(n , "n", "10"));
        _i_def(proc , "proc", "10");
      	if (_i_node("11") && (_i_puse(proc , "proc"))) {
          _i_loc("11", "12");
          _i_node("12");
      	    src_queue = del_ele(_i_cuse(src_queue , "src_queue", "12"), _i_cuse(proc , "proc", "12"));
            _i_def(src_queue , "src_queue", "12");
      	    /* append to appropriate prio queue */
            _i_node("13");
      	    proc->priority = _i_cuse(prio , "prio", "13");
            _i_def(proc , "proc", "13");
            _i_node("14");
      	    dest_queue = append_ele(_i_cuse(dest_queue , "dest_queue", "14"), _i_cuse( proc, "proc", "14"));
      	}else{
          _i_loc("11", "15");
          _i_node("15");
        }
    }else{
      _i_loc("8", "16");
      _i_node("16");
    }
}

void
unblock_process(ratio)
float ratio;
{
  _i_function("unblock_process");
  _i_node("0");
  _i_def(ratio , "ratio", "0");
  _i_node("1");
    int count;
    int n;
    Ele *proc;
    int prio;
    _i_def(count , "count", "1");
    _i_def(n , "n", "1");
    _i_def(proc , "proc", "1");
    _i_def(prio , "prio", "1");

    if (_i_node("2")&&(_i_puse(block_queue , "block_queue","global")))
    {
      _i_loc("2", "3");
      _i_node("3");
    	count = _i_cuse(block_queue->mem_count , "block_queue", "3","global");
      _i_def(count , "count", "3");
      _i_node("4");
    	n = (int) (_i_cuse(count , "count", "4")*_i_cuse(ratio , "ratio", "4") + 1);
      _i_def(n , "n", "4");
      _i_node("5");
    	proc = find_nth(_i_cuse(block_queue , "block_queue", "5","global"), _i_cuse(n , "n", "5"));
      _i_def(proc , "proc", "5");

    	if (_i_node("6") && (_i_puse(proc , "proc"))) {
        _i_loc("6", "7");
        _i_node("7");
    	    block_queue = del_ele(_i_cuse(block_queue , "block_queue", "7","global"), _i_cuse(proc , "proc", "7"));
          _i_def(block_queue , "block_queue", "7","global");
          _i_node("8");
    	    /* append to appropriate prio queue */
    	    prio =_i_cuse( proc->priority, "proc", "8");
          _i_def(prio , "prio", "8");
          _i_node("9");
    	    prio_queue[_i_cuse(prio , "prio", "9")] = append_ele(_i_cuse(prio_queue[_i_cuse(prio , "prio", "9")] , "prio_queue", "9","global"), _i_cuse(proc , "proc", "9"));
          _i_def(prio_queue , "prio_queue", "9","global");
    	}else{
        _i_loc("6", "10");
        _i_node("10");
      }
    }else{
      _i_loc("2", "11");
      _i_node("11");
    }
}

void quantum_expire()
{
  _i_function("quantum_expire");
  _i_node("0");
  _i_node("1");
    int prio;
    _i_def(prio , "prio", "1");
    schedule();
    if (_i_node("2") && (_i_puse(cur_proc , "cur_proc","global")))
    {
      _i_loc("2", "3");
      _i_node("3");
    	prio = _i_cuse(cur_proc->priority , "cur_proc", "3","global");
      _i_def(prio , "prio", "3");
      _i_node("4");
    	prio_queue[_i_cuse(prio , "prio", "4")] = append_ele(_i_cuse(prio_queue[_i_cuse(prio , "prio", "4")] , "prio_queue", "4","global"), _i_cuse(cur_proc , "cur_proc", "4","global"));
      _i_def(prio_queue , "prio_queue", "4","global");
    }else{
      _i_loc("2", "5");
      _i_node("5");
    }
}

void
block_process()
{
  _i_function("block_process");
  _i_node("0");
  _i_node("1");
    schedule();
    if (_i_node("2")&&(_i_puse(cur_proc , "cur_proc","global"))){
      _i_loc("2", "3");
      _i_node("3");
	     block_queue = append_ele(_i_cuse(block_queue , "block_queue", "3","global"), _i_cuse(cur_proc , "cur_proc", "3","global"));
       _i_def(block_queue , "block_queue", "3","global");
    }else{
      _i_loc("2", "4");
      _i_node("4");
    }
}

Ele * new_process(prio)
int prio;
{
  _i_function("new_process");
  _i_node("0");
  _i_def(prio , "prio", "0");
  _i_node("1");
    Ele *proc;
    _i_def(proc , "proc", "1");
    _i_node("2");
    proc = new_ele(_i_def(_i_cuse(alloc_proc_num++ , "alloc_proc_num", "2","global") , "alloc_proc_num", "2","global"));
    _i_def(proc , "proc", "2");
    _i_node("3");
    proc->priority = _i_cuse(prio , "prio", "3");
    _i_def(proc->priority , "proc->priority", "3");
    _i_node("4");
    _i_def(_i_cuse(num_processes++ , "num_processes", "4","global") , "num_processes", "4","global");
    _i_node("5");
    return _i_cuse(proc , "proc", "5");
}

void add_process(prio)
int prio;
{
  _i_function("add_process");
  _i_node("0");
  _i_def(prio , "prio", "prio");
  _i_node("1");
    Ele *proc;
    _i_def(proc , "proc", "1");
    _i_node("2");
    proc = new_process(_i_cuse(prio , "prio", "2"));
    _i_node("proc");
    _i_node("3");
    prio_queue[_i_cuse(prio , "prio", "3")] = append_ele(_i_cuse(prio_queue[_i_cuse(prio , "prio", "3")] , "prio_queue", "3","global"), _i_cuse(proc , "proc", "3"));
    _i_def(prio_queue , "prio_queue", "3","global");
}

void init_prio_queue(prio, num_proc)
int prio;
int num_proc;
{
  _i_function("init_prio_queue");
  _i_node("0");
  _i_def(prio , "prio", "0");
  _i_def(num_proc , "num_proc", "0");

  _i_node("1");
    List *queue;
    Ele  *proc;
    int i;

    _i_def(queue , "queue", "1");
    _i_def(proc , "proc", "1");
    _i_def(i , "i", "1");

    _i_node("2");
    queue = new_list();
    _i_def(queue , "queue", "2");

    for (_i_node("3"),i=0,_i_def(i , "i", "3");_i_node("4")&& (_i_puse(i , "i")<_i_puse(num_proc , "num_proc"));_i_node("7"),_i_def(_i_cuse(i++ , "i", "7") , "i", "7") )
    {
      _i_loc("4", "5");
      _i_node("5");
    	proc = new_process(_i_cuse(prio , "prio", "5"));
      _i_def(proc , "proc", "5");
      _i_node("6");
    	queue = append_ele(_i_cuse(queue , "queue", "6"), _i_cuse(proc , "proc", "6"));
      _i_def(queue , "queue", "6");
    }
    _i_loc("4", "7");
    _i_node("7");
    prio_queue[_i_cuse(prio , "prio", "7")] = _i_cuse(queue , "queue", "7");
    _i_def(prio_queue , "prio_queue", "7","global");
}

void initialize()
{
  _i_function("initialize");
  _i_node("0");
  _i_node("1");
    alloc_proc_num = 0;
    num_processes = 0;
    _i_def(alloc_proc_num , "alloc_proc_num", "1","global");
    _i_def(num_processes , "num_processes", "1","global");
}

/* test driver */
main(argc, argv)
int argc;
char *argv[];
{
  global_sets();
  _i_function("main");
  _i_node("0");
  _i_def(argc , "argc", "0");
  _i_def(argv , "argv", "0");
  _i_node("1");
    int command;
    int prio;
    float ratio;
    int status;
    _i_def(command , "command", "1");
    _i_def(prio , "prio", "1");
    _i_def(ratio , "ratio", "1");
    _i_def(status , "status", "1");


    if (_i_node("2")&&(_i_puse(argc , "argc") < (_i_puse(MAXPRIO , "MAXPRIO","global")+1)))
    {
      _i_loc("2", "3");
      _i_node("3");
    	fprintf(stdout, "incorrect usage\n");
    	return;
    }else{
      _i_loc("2", "4");
      _i_node("4");
    }

    _i_node("5");
    initialize();
    for (_i_node("6"),prio=_i_cuse(MAXPRIO , "MAXPRIO", "6","global"),_i_def(prio , "prio", "6");_i_node("7")&& (_i_puse(prio , "prio") >= 1);_i_node("9"),_i_def(_i_cuse(prio-- , "priox", "9") , "prio", "9"))
    {
      _i_loc("7", "8");
      _i_node("8");
	       init_prio_queue(_i_cuse(prio , "prio", "8"), atoi(_i_cuse(argv[_i_cuse(prio , "prio", "8")] , "argv", "8")));
    }
    _i_loc("7", "10");

    for (_i_node("10"),status = fscanf(stdin, "%d", &command),_i_def(command , "command", "10"),_i_def(status , "status", "10");_i_node("11")&& ((_i_puse(status , "status")!=_i_puse(EOF , "EOF")) && _i_puse(status , "status"));_i_node("?"), status = fscanf(stdin, "%d", &command),_i_def(command , "command", "?"),_i_def(status , "status", "?"))
    {
      _i_loc("11", "12");

      	switch(command)
      	{
      	case FINISH:
            _i_node("12");
            _i_puse(command , "command");
            _i_puse(FINISH , "FINISH","global");
            _i_loc("12", "13");
            _i_node("13");
      	    finish_process();
            _i_node("14");
      	    break;
      	case BLOCK:
            _i_node("12");
            _i_puse(command , "command");
            _i_puse(BLOCK , "BLOCK","global");
            _i_loc("12", "15");
            _i_node("15");
      	    block_process();
            _i_node("16");
      	    break;
      	case QUANTUM_EXPIRE:
            _i_node("12");
            _i_puse(command , "command");
            _i_puse(QUANTUM_EXPIRE , "QUANTUM_EXPIRE","global");
            _i_loc("12", "17");
            _i_node("17");
      	    quantum_expire();
            _i_node("18");
      	    break;
      	case UNBLOCK:
            _i_node("12");
            _i_puse(command , "command");
            _i_puse(UNBLOCK , "UNBLOCK","global");
            _i_loc("12", "19");
            _i_node("19");
      	    fscanf(stdin, "%f", &ratio);
            _i_def(ratio , "ratio", "19");
            _i_node("20");
      	    unblock_process(_i_cuse(ratio , "ratio", "20"));
            _i_node("21");
      	    break;
      	case UPGRADE_PRIO:
            _i_node("12");
            _i_puse(command , "command");
            _i_puse(UPGRADE_PRIO , "UPGRADE_PRIO","global");
            _i_loc("12", "22");
            _i_node("22");

      	    fscanf(stdin, "%d", &prio);
            _i_def(prio , "prio", "22");
            _i_node("23");
      	    fscanf(stdin, "%f", &ratio);
            _i_def(ratio , "ratio", "23");

            if (_i_node("24") && (_i_puse(prio , "prio") > _i_puse(MAXPRIO , "MAXPRIO","global") || _i_puse(prio , "prio") <= 0)) {
              _i_loc("24", "25");
              _i_node("25");
          		fprintf(stdout, "** invalid priority\n");
          		return;
      	    }
      	    else{
              _i_loc("24", "26");
              _i_node("26");
      		      upgrade_process_prio(_i_cuse(prio , "prio", "26"), _i_cuse(ratio , "ratio", "26"));
            }
            _i_node("27");
      	    break;
      	case NEW_JOB:
            _i_node("12");
            _i_puse(command , "command");
            _i_puse(NEW_JOB , "NEW_JOB","global");
            _i_loc("12", "28");
            _i_node("28");
      	    fscanf(stdin, "%d", &prio);
            _i_def(prio , "prio", "29");
      	    if (_i_node("30") && (_i_puse(prio , "prio") > _i_puse(MAXPRIO , "MAXPRIO","global") || _i_puse(prio , "prio") <= 0)) {
              _i_loc("30", "31");
              _i_node("31");
          		fprintf(stdout, "** invalid priority\n");
          		return;
      	    }
      	    else{
              _i_loc("30", "32");
              _i_node("32");
      		      add_process(_i_cuse(prio , "prio", "32"));
            }
            _i_node("33");
      	    break;
      	case FLUSH:
            _i_node("12");
            _i_puse(command , "command");
            _i_puse(FLUSH , "FLUSH","global");
            _i_loc("12", "34");
            _i_node("34");
      	    finish_all_processes();
      	    break;
      	}
    }
}

/* A simple input spec:

  a.out n3 n2 n1

  where n3, n2, n1 are non-negative integers indicating the number of
  initial processes at priority 3, 2, and 1, respectively.

  The input file is a list of commands of the following kinds:
   (For simplicity, comamnd names are integers (NOT strings)

  FINISH            ;; this exits the current process (printing its number)
  NEW_JOB priority  ;; this adds a new process at specified priority
  BLOCK             ;; this adds the current process to the blocked queue
  QUANTUM_EXPIRE    ;; this puts the current process at the end
                    ;;      of its prioqueue
  UNBLOCK ratio     ;; this unblocks a process from the blocked queue
                    ;;     and ratio is used to determine which one

  UPGRADE_PRIO small-priority ratio ;; this promotes a process from
                    ;; the small-priority queue to the next higher priority
                    ;;     and ratio is used to determine which process

  FLUSH	            ;; causes all the processes from the prio queues to
                    ;;    exit the system in their priority order

where
 NEW_JOB        1
 UPGRADE_PRIO   2
 BLOCK          3
 UNBLOCK        4
 QUANTUM_EXPIRE 5
 FINISH         6
 FLUSH          7
and priority is in        1..3
and small-priority is in  1..2
and ratio is in           0.0..1.0

 The output is a list of numbers indicating the order in which
 processes exit from the system.

*/
