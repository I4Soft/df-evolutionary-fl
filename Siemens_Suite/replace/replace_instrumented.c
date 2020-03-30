/*  -*- Last-Edit:  Mon Dec  7 10:31:51 1992 by Tarak S. Goradia; -*- */

extern void	exit();
# include <stdio.h>

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

void	Caseerror();

typedef char	bool;
# define false 0
# define true  1
# define NULL 0

# define MAXSTR 100
# define MAXPAT MAXSTR

# define ENDSTR  '\0'
# define ESCAPE  '@'
# define CLOSURE '*'
# define BOL     '%'
# define EOL     '$'
# define ANY     '?'
# define CCL     '['
# define CCLEND  ']'
# define NEGATE  '^'
# define NCCL    '!'
# define LITCHAR 'c'
# define DITTO   -1
# define DASH    '-'

# define TAB     9
# define NEWLINE 10

# define CLOSIZE 1

typedef char	character;
typedef char string[MAXSTR];

bool
  getline(s, maxsize)
char	*s;
int	maxsize;
{
    _i_function("getline");
    _i_node("0");
    _i_def(s , "s", "0");
    _i_def(maxsize , "maxsize", "0");

    _i_node("1");
    char *result;
    _i_def(result , "result", "1");
    _i_node("2");
    result = fgets(_i_cuse(s , "s", "2"), _i_cuse(maxsize , "maxsize", "2"), stdin);
    _i_def(result , "result", "2");
    _i_node("3");
    return (_i_cuse(result , "result", "3") != NULL);
}
int
addstr(c, outset, j, maxset)
char	c;
char	*outset;
int	*j;
int	maxset;
{
    _i_function("addstr");
    _i_node("0");
    _i_def(c , "c", "0");
    _i_def(outset , "outset", "0");
    _i_def(j , "j", "0");
    _i_def(maxset , "maxset", "0");

    _i_node("1");
    bool	result;
    _i_def(result , "result", "1");

    if (_i_node("2") && (_i_puse(*j , "j") >= _i_puse(maxset , "maxset"))){
      _i_loc("2", "3");
      _i_node("3");
       result = false;
       _i_def( result, "result", "3");
     }
    else {
      _i_loc("2", "4");
      _i_node("4");
	     outset[_i_cuse(*j , "j", "4")] = _i_cuse(c , "c", "4");
       _i_def(outset , "outset", "4");

       _i_node("5");
	     *j = _i_cuse( *j, "j", "5") + 1;
       _i_def(j , "j", "6");
	     result = true;
       _i_def(result , "result", "6");
    }
    _i_node("7");
    return _i_cuse( result, "result", "7");
}

char
esc(s, i)
char 	*s;
int	*i;
{
  _i_function("esc");
  _i_node("0");
  _i_def(s , "s", "0");
  _i_def(i , "i", "0");

  _i_node("1");
    char	result;
  _i_def(result , "result", "1");



    if (  _i_node("2")&&(_i_puse(s[_i_cuse(*i , "i", "2")] , "s") != _i_puse(ESCAPE , "ESCAPE"))){
      _i_loc("2", "3");
      _i_node("3");
      result = _i_cuse(s[_i_cuse(*i , "i", "3")] , "s", "3");
      _i_def(result , "result", "3");
     }
    else
    {
      _i_loc("2", "4");

    	if (_i_node("4") && (_i_puse(s[_i_cuse( *i, "i", "4") + 1] , "s") == _i_puse(ENDSTR , "ENDSTR")))
      {
        _i_loc("4", "5");
        _i_node("5");
    	  result = _i_cuse(ESCAPE , "ESCAPE", "5");
        _i_def(result , "result", "5");
      }
    	else
    	{
        _i_loc("4", "6");
        _i_node("6");
    	   *i = _i_cuse(*i , "i", "6") + 1;
         _i_def(i , "i", "6");

         if (_i_node("7") && (_i_puse(s[_i_cuse(*i , "i", "7")] , "s") == 'n')){
           _i_loc("7", "8");
           _i_node("8");
    		    result = _i_cuse(NEWLINE , "NEWLINE", "8");
            _i_def( result , "result", "8");
        }
    	   else
         {
           _i_loc("7", "9");

      		if (_i_node("9") && (_i_puse(s[_i_cuse(*i , "i", "9")] , "s") == 't'))
          {
            _i_loc("9", "10");
            _i_node("10");
      		    result = _i_cuse(TAB , "TAB", "10");
              _i_def(result , "result", "10");
            }
      		else{
            _i_loc("9", "11");
            _i_node("11");
      		   result = _i_cuse( s[_i_cuse(*i , "i", "11")] , "s", "11");
            _i_def(result , "result", "11");
            }
        }
    	}
    }
    _i_node("12");
    return _i_cuse(result , "result", "12");
}

void change();

 void
dodash(delim, src, i, dest, j, maxset)
char	delim;
char	*src;
int	*i;
char	*dest;
int	*j;
int	maxset;
{
  _i_function("dodash");
  _i_node("0");
  _i_def(delim , "delim", "0");
  _i_def(src , "src", "0");
  _i_def(i , "i", "0");
  _i_def(dest , "dest", "0");
  _i_def(j , "j", "0");
  _i_def(maxset , "maxset", "0");

  _i_node("1");
    int	k;
    _i_def(k , "k", "1");

    bool	junk;
    _i_def(junk , "junk", "1");

    char	escjunk;
    _i_def(escjunk , "escjunk", "1");


    while ( _i_node("2") && ((_i_puse(src[_i_cuse(*i , "i", "2")] , "src") != _i_puse(delim , "delim")) && (_i_puse(src[_i_cuse(*i , "i", "2")] , "src") != _i_puse( ENDSTR, "ENDSTR","global"))))
    {
      _i_loc("2", "3");
      _i_node("3");

    	if (_i_node("4") && _i_puse(src[_i_cuse(*i , "i", "4") - 1] , "src") == _i_puse(ESCAPE , "ESCAPE","global")) {
          _i_loc("4", "5");
    	    escjunk = esc(_i_cuse( src, "src", "5"), _i_cuse(i , "i", "5"));
          _i_def(escjunk , "escjunk", "5");
    	    junk = addstr(_i_cuse(escjunk , "escjunk", "5"), _i_cuse(dest , "dest", "5"), _i_cuse( j, "j", "5"), _i_cuse(maxset , "maxset", "5"));
    	} else
        {
          _i_loc("4", "6");

    	    if (_i_node("6") && (_i_puse(src[_i_cuse(*i , "i", "6")] , "src") != _i_puse(DASH , "DASH","global")))
          {
            _i_loc("6", "7");
            _i_node("7");
    		    junk = addstr(_i_cuse(src[_i_cuse(*i , "i", "7")] , "src", "7"), _i_cuse(dest , "dest", "7"), _i_cuse(j , "j", "7"), _i_cuse(maxset , "maxset", "7"));
            _i_def(junk , "junk", "7");
          }
    	    else
            {
              _i_loc("6", "8");

            if (_i_node("8") && (_i_puse(*j , "j") <= 1 || _i_puse(src[_i_cuse(*i , "i", "8") + 1] , "src") == _i_puse( ENDSTR, "ENDSTR","global")))
              {
                  _i_loc("8", "9");
                  _i_node("9");
      		        junk = addstr(_i_cuse(DASH , "DASH", "9"), _i_cuse( dest, "dest", "9"), _i_cuse(j , "j", "9"), _i_cuse(maxset , "maxset", "9"));
                  _i_def(junk , "junk", "9");
              }
      	    else
            {
              _i_loc("8", "10");

              if (_i_node("10") && ((isalnum(_i_puse(src[_i_cuse(*i , "i", "10") - 1] , "src"))) && (isalnum(_i_puse(src[_i_cuse(*i , "i", "10") + 1] , "src")))&& (_i_puse(src[_i_cuse(*i , "i", "10") - 1] , "src") <= _i_puse(src[_i_cuse(*i , "i", "10") + 1] , "src"))))
      		     {
                 _i_loc("10", "11");

          		    for ( _i_node("11"),k = _i_cuse(src[_i_cuse(*i , "i", "11")-1] , "src", "11")+1,_i_def(k , "k", "11") ; _i_node("12") && (_i_puse(k , "k")<=_i_puse(src[_i_cuse(*i , "i", "12")+1] , "src")); _i_node("14"), _i_def(_i_cuse(k++ , "k", "14") , "k", "14"))
          		    {
                    _i_loc("12", "13");
                    _i_node("13");
          			       junk = addstr(_i_cuse(k , "k", "13"), _i_cuse(dest , "dest", "13"), _i_cuse(j , "j", "13"), _i_cuse(maxset , "maxset", "13"));
                    _i_def(junk , "junk", "13");
          		    }
                  _i_loc("12", "15");
                  _i_node("15");
        		      *i = _i_cuse(*i , "i", "15") + 1;
                  _i_def(*i , "i", "15");
      		      }
        	    else
              {
                _i_loc("10", "16");
                _i_node("16");
          		    junk = addstr(_i_cuse(DASH , "DASH", "16","global"), _i_cuse(dest , "dest", "16"), _i_cuse( j, "j", "16"), _i_cuse( maxset, "maxset", "16"));
                  _i_def(junk , "junk", "16");
              }
            }
          }
        }
        _i_node("17");
	     (*i) = (_i_cuse(*i , "i", "17")) + 1;
       _i_def(*i , "i", "17");
    }
    _i_loc("2", "18");
    _i_node("18");
}

bool
getccl(arg, i, pat, j)
char	*arg;
int	*i;
char	*pat;
int	*j;
{
  _i_function("getccl");
  _i_node("0");
  _i_def(arg , "arg", "0");
  _i_def(i , "i", "0");
  _i_def(pat , "pat", "0");
  _i_def(j , "j", "0");

  _i_node("1");
    int	jstart;
    bool	junk;
    _i_def(jstart , "jstart", "1");
    _i_def(junk , "junk", "1");

    _i_node("2");
    *i = _i_cuse(*i , "i", "2") + 1;
    _i_def(i , "i", "2");

    if (_i_node("3") &&(_i_puse(arg[_i_cuse(*i , "i", "3")] , "arg") == _i_puse(NEGATE , "NEGATE","global"))) {
      _i_loc("3", "4");
      _i_node("4");
	     junk = addstr(_i_cuse(NCCL , "NCCL", "4","global"), _i_cuse(pat , "pat", "4"), _i_cuse(j , "j", "4"), _i_cuse(MAXPAT , "MAXPAT", "4","global"));
      _i_def(junk , "junk", "4");
      _i_node("5");
        *i = _i_cuse(*i , "i", "5") + 1;
        _i_def(*i , "i", "5");

    } else{
      _i_loc("3", "6");
      _i_node("6");
	     junk = addstr(_i_cuse(CCL , "CCL", "6","global"), _i_cuse(pat , "pat", "6"), _i_cuse(j , "j", "6"), _i_cuse(MAXPAT , "MAXPAT", "6","global"));
       _i_def(junk , "junk", "6");
     }
     _i_node("7");
    jstart = _i_cuse(*j , "j", "7");
    _i_def(jstart , "jstart", "7");
    _i_node("8");
    junk = addstr(0, _i_cuse(pat , "pat", "8"), _i_cuse(j , "j", "8"), _i_cuse(MAXPAT , "MAXPAT", "8","global"));
    _i_node("9");
    dodash(_i_cuse(CCLEND , "CCLEND", "9","global"), _i_cuse(arg , "arg", "9"), _i_cuse(i , "i", "9"), _i_cuse(pat , "pat", "9"), _i_cuse( j, "j", "9"), _i_cuse(MAXPAT , "MAXPAT", "9"));
    _i_node("10");
    pat[_i_cuse(jstart , "jstart", "10")] = _i_cuse(*j , "j", "10") - _i_cuse(jstart , "jstart", "10") - 1;
    _i_def(pat , "pat", "10");
    _i_node("11");
    return (_i_cuse(arg[_i_cuse(*i , "i", "11")] , "arg", "11") == _i_cuse(CCLEND , "CCLEND", "11"));
}

 void
stclose(pat, j, lastj)
char	*pat;
int	*j;
int	lastj;
{
    _i_function("stclose");
    _i_node("0");
    _i_def(pat , "pat", "0");
    _i_def(j , "j", "0");
    _i_def(lastj , "lastj", "0");

    _i_node("1");
    int	jt;
    int	jp;
    bool	junk;
    _i_def(jt , "jt", "1");
    _i_def(jp , "jp", "1");
    _i_def(junk , "junk", "1");



    for (_i_node("2"),jp = _i_cuse(*j , "j", "2") - 1,_i_def(jp , "jp", "2");_i_node("3") && (_i_puse(jp , "jp") >= _i_puse(lastj , "lastj"));_i_node("6"), _i_def(_i_cuse(jp-- , "jp", "6") , "jp", "6"))
    {
      _i_loc("3", "4");
      _i_node("4");
	    jt = _i_cuse(jp , "jp", "4") + _i_cuse(CLOSIZE , "CLOSIZE", "4");
      _i_def(jt , "jt", "4");
      _i_node("5");
	    junk = addstr(_i_cuse(pat[_i_cuse(jp , "jp", "5")] , "pat", "5"), _i_cuse(pat , "pat", "5"), _i_cuse(&jt , "jt", "5"), _i_cuse(MAXPAT , "MAXPAT", "5","global"));
      _i_def( junk, "junk", "5");
    }
    _i_loc("3", "7");
    _i_node("7");
    *j = _i_cuse(*j , "j", "7") + _i_cuse(CLOSIZE , "CLOSIZE", "7","global");
    _i_def(j , "j", "7");
    _i_node("8");
    pat[_i_cuse(lastj , "lastj", "8")] = _i_cuse(CLOSURE , "CLOSURE", "8","global");
    _i_def(pat , "pat", "8");
}

bool in_set_2(c)
char c;
{
  _i_function("in_set_2");
  _i_node("0");
  _i_def(c , "c", "0");
  _i_node("1");
  return (_i_cuse(c , "c", "1") == _i_cuse(BOL , "BOL", "1","global") || _i_cuse(c , "c", "1") == _i_cuse(EOL , "EOL", "1","global") || _i_cuse(c , "c", "1") == _i_cuse(CLOSURE , "CLOSURE", "1","global"));
}

bool in_pat_set(c)
char c;
{
  _i_function("in_pat_set");
  _i_node("0");
  _i_def(c , "c", "0");
  _i_node("1");

  return (   _i_cuse(c , "c", "1") == _i_cuse(LITCHAR , "LITCHAR", "1", "global") || _i_cuse(c , "c", "1") == _i_cuse(BOL , "BOL", "1","global")  || _i_cuse(c , "c", "1") == _i_cuse(EOL , "EOL", "1","global") || _i_cuse(c , "c", "1") == _i_cuse(ANY , "ANY", "1","global")
          || _i_cuse(c , "c", "1") == _i_cuse(CCL , "CCL", "1","global")     || _i_cuse(c , "c", "1") == _i_cuse(NCCL , "NCCL", "1", "global") || _i_cuse(c , "c", "1") == _i_cuse(CLOSURE , "CLOSURE", "1","global"));
}

int
makepat(arg, start, delim, pat)
char	*arg;
int	start;
char	delim;
char	*pat;
{
  _i_function("makepat");
  _i_node("0");
  _i_def(arg , "arg", "0");
  _i_def(start , "start", "0");
  _i_def(delim , "delim", "0");
  _i_def(pat , "pat", "0");


  _i_node("1");
    int	result;
    int	i, j, lastj, lj;
    bool	done, junk;
    bool	getres;
    char	escjunk;
    _i_def(result , "result", "1");
    _i_def(i , "i", "1");
    _i_def(j , "j", "1");
    _i_def(lastj , "lastj", "1");
    _i_def(lj , "lj", "1");
    _i_def(done , "done", "1");
    _i_def(junk , "junk", "1");
    _i_def(getres , "getres", "1");
    _i_def(escjunk , "escjunk", "1");

    _i_node("2");
    j = 0;
    _i_def(j , "j", "2");
    i = _i_cuse(start , "start", "2");
    lastj = 0;
    _i_def(lastj , "lastj", "2");
    done = false;
    _i_def(done , "done", "2");

    while (_i_node("3") && ((_i_puse(!done , "done")) && (_i_puse(arg[_i_cuse(i , "i", "3")] , "arg") != _i_puse(delim , "delim")) && (_i_puse(arg[_i_cuse(i , "i", "3")] , "arg") != _i_puse(ENDSTR , "ENDSTR","global")))) {
        _i_loc("3", "4");
        _i_node("4");

        lj = _i_cuse(j , "j", "4");
        _i_def(lj , "lj", "4");

      	if (_i_node("5") && (_i_puse(arg[_i_cuse(i , "i", "5")] , "arg") == _i_puse(ANY , "ANY","global"))){
            _i_loc("5", "6");
            _i_node("6");
            junk = addstr(_i_cuse(ANY , "ANY", "6","global"), _i_cuse(pat , "pat", "6"), _i_cuse(&j , "j", "6"), _i_cuse(MAXPAT , "MAXPAT", "6","global"));
            _i_def(junk , "junk", "6");
          }
        else{
          _i_loc("5", "7");

            if (_i_node("7") && ((_i_puse(arg[_i_cuse(i , "i", "7")] , "arg") == _i_puse(BOL , "BOL","global")) && (_i_puse(i , "i") == _i_puse(start , "start")))){
              _i_loc("7", "8");
              _i_node("8");
               junk = addstr(_i_cuse(BOL , "BOL", "8","global"), _i_cuse(pat , "pat", "8"), _i_cuse(&j , "j", "8"), _i_cuse(MAXPAT , "MAXPAT", "8","global"));
               _i_def( junk, "junk", "8");
              }
        	  else{
              _i_loc("7", "9");
               if (_i_node("9") &&((_i_puse(arg[_i_cuse(i , "i", "9")] , "arg") == _i_puse(EOL , "EOL","global")) && (_i_puse(arg[_i_cuse(i , "i", "9")+1] , "arg") == _i_puse(delim , "delim")))){
                 _i_loc("9", "10");
                 _i_node("10");
                  junk = addstr(_i_cuse(EOL , "EOL", "10","global"), _i_cuse(pat , "pat", "10"), _i_cuse(&j , "j", "10"), _i_cuse(MAXPAT , "MAXPAT", "10","global"));
                  _i_def( junk, "junk", "10");

                }
          	    else{
                  _i_loc("9", "11");
                   if ( _i_node("11") && (_i_puse(arg[_i_cuse(i , "i", "11")] , "arg") == _i_puse(CCL , "CCL", "global"))){
                    _i_loc("11", "12");
                    _i_node("12");
                    getres = getccl(_i_cuse(arg , "arg", "12"), _i_cuse(&i , "i", "12"), _i_cuse(pat , "pat", "12"), _i_cuse(&j , "j", "12"));
                    _i_def(getres , "getres", "12");
                    _i_node("13");
              	    done = (bool)(_i_cuse(getres , "getres", "13") == false);
                    _i_def(done , "done", "13");
            	     }

            	    else{
                    _i_loc("11", "14");

                      if (_i_node("14") &&((_i_puse(arg[_i_cuse(i , "i", "14")] , "arg") == _i_puse(CLOSURE , "CLOSURE","global")) && (_i_puse(i , "i") > _i_puse(start , "start")))){
                        _i_loc("14", "15");
                        _i_node("15");
                         lj = _i_cuse(lastj , "lastj", "15");
                         _i_def(lj , "lj", "15");

                    	    if (_i_node("16") &&(in_set_2(_i_puse(pat[_i_cuse(lj , "lj", "16")] , "pat")))){
                            _i_loc("16", "17");
                            _i_node("17");
                              done = true;
                              _i_def(done , "done", "17");
                            }
                    	    else{
                            _i_loc("16", "18");
                            _i_node("18");
                    		      stclose(_i_cuse(pat , "pat", "18"), _i_cuse(&j , "j", "18"), _i_cuse(lastj , "lastj", "19"));
                            }
                	    }
                    	else
                    	{
                        _i_loc("14", "19");
                        _i_node("19");
                    	    junk = addstr(_i_cuse(LITCHAR , "LITCHAR", "19","global"), _i_cuse( pat, "pat", "19"), _i_cuse(&j , "j", "19"), _i_cuse(MAXPAT , "MAXPAT", "19","global"));
                          _i_def(junk , "junk", "19");
                          _i_node("20");
                    	    escjunk = esc(_i_cuse(arg , "arg", "20"), _i_cuse(&i , "i", "20"));
                          _i_def(escjunk , "escjunk", "20");
                          _i_node("21");
                    	    junk = addstr(_i_cuse(escjunk , "escjunk", "21"), _i_cuse(pat , "pat", "21"), _i_cuse(&j , "j", "21"), _i_cuse(MAXPAT , "MAXPAT", "21","global"));

                    	}
                  }
                }
            }
        }
        _i_node("22");
      	lastj = _i_cuse(lj , "lj", "22");
        _i_def(lastj , "lastj", "22");
      	if (_i_node("23") && (!_i_puse(done , "done"))){
          _i_loc("23", "24");
          _i_node("24");
            i = _i_cuse(i , "i", "24") + 1;
            _i_def(i , "i", "24");
          }
          else{
            _i_loc("23", "25");
            _i_node("25");
          }
    }
    _i_loc("3", "26");
    _i_node("26");

    junk = addstr(_i_cuse(ENDSTR , "ENDSTR", "26","global"), _i_cuse(pat , "pat", "26"), _i_cuse(&j , "j", "26"), _i_cuse(MAXPAT , "MAXPAT", "26","global"));
    _i_def(junk , "junk", "26");
    if (_i_node("27") && ((_i_puse(done , "done")) || (_i_puse(arg[_i_cuse(i , "i", "27")] , "arg") != _i_puse(delim , "delim")))){
      _i_loc("27", "28");
      _i_node("28");
       result = 0;
       _i_def( result, "result", "28");
    }
    else{
      _i_loc("27", "29");

    	if (_i_node("29") && (!_i_cuse( junk, "junk", "29"))){
          _i_loc("29", "30");
          _i_node("30");
          result = 0;
          _i_def(result , "result", "30");
        }
    	else{
        _i_loc("29", "31");
        _i_node("31");

    	    result = _i_cuse(i , "i", "31");
          _i_def(result , "result", "31");

        }
    }
    _i_node("32");
    return _i_cuse(result , "result", "32");
}

int
getpat(arg, pat)
char*	arg;
char*	pat;
{
    _i_function("getpat");
    _i_node("0");
    _i_def(arg , "arg", "0");
    _i_def(pat , "pat", "0");

    _i_node("1");
    int	makeres;
    _i_def(makeres , "makeres", "1");

    _i_node("2");
    makeres = makepat(_i_cuse(arg , "arg", "2"), 0, _i_cuse(ENDSTR , "ENDSTR", "2","global"), _i_cuse(pat , "pat", "2"));
    _i_def(makeres , "makeres", "2");
    _i_node("3");
    return (_i_cuse(makeres , "makeres", "3") > 0);
}

int
makesub(arg, from, delim, sub)
	char*	arg;
	int	from;
	character	delim;
	char*	sub;
{
  _i_function("makesub");
    _i_node("0");
    _i_def(arg , "arg", "0");
    _i_def(from , "from", "0");
    _i_def(delim , "delim", "0");
    _i_def(sub , "sub", "0");


    _i_node("1");
    int  result;
    int	i, j;
    bool	junk;
    character	escjunk;
    _i_def(result , "result", "1");
    _i_def(i , "i", "1");
    _i_def(j , "j", "1");
    _i_def(junk , "junk", "1");
    _i_def(escjunk , "escjunk", "1");

    _i_node("2");
    j = 0;
    _i_def(j , "j", "2");
    _i_node("3");
    i = _i_cuse(from , "from", "3");
    _i_def(i , "i", "3");

    while (_i_node("4") && ((_i_puse(arg[_i_cuse(i , "i", "4")] , "arg") != _i_puse(delim , "delim")) && (_i_puse(arg[_i_cuse(i , "i", "4")] , "arg") != _i_puse(ENDSTR , "ENDSTR","global")))) {
      _i_loc("4", "5");

        if (_i_node("5") &&(_i_puse(arg[_i_cuse(i , "i", "5")] , "arg") == (unsigned)('&'))){
            _i_loc("5", "6");
            _i_node("6");
            junk = addstr(_i_cuse(DITTO , "DITTO", "6","global"), _i_cuse(sub , "sub", "6"), _i_cuse(&j , "j", "6"), _i_cuse(MAXPAT , "MAXPAT", "6","global"));
            _i_def(junk , "junk", "6");
          }
      	else {
          _i_loc("5", "7");
          _i_node("7");
      	    escjunk = esc(_i_cuse(arg , "arg", "7"), _i_cuse(&i , "i", "7"));
            _i_def(escjunk , "escjunk", "7");
            _i_node("8");
      	    junk = addstr(_i_cuse(escjunk , "escjunk", "8"), _i_cuse(sub , "sub", "8"), _i_cuse(&j , "j", "8"), _i_cuse(MAXPAT , "MAXPAT", "8","global"));
      	}
        _i_node("9");
      	i = _i_cuse(i , "i", "9") + 1;
        _i_def( i, "i", "9");
    }
    _i_loc("4", "10");

    if (_i_node("10")&& (_i_puse(arg[_i_cuse(i , "i", "10")] , "arg") != _i_puse(delim , "delim"))){
      _i_loc("10", "11");
      _i_node("11");
       result = 0;
       _i_def(result , "result", "11");
     }
    else {
      _i_loc("10", "12");
      _i_node("12");
    	junk = addstr(_i_cuse(ENDSTR , "ENDSTR", "12"), _i_cuse(&(*sub) , "sub", "12"), _i_cuse(&j , "j", "12"), _i_cuse(MAXPAT , "MAXPAT", "12","global"));
      _i_def(junk , "junk", "12");
      if (_i_node("13") && (!_i_puse(junk , "junk"))){
          _i_loc("13", "14");
          _i_node("14");
          result = 0;
          _i_def(result , "result", "14");
      }
    	else{
        _i_loc("13", "15");
        _i_node("15");
    	    result = _i_cuse(i , "i", "15");
          _i_def(result , "result", "15");
        }
    }
    _i_node("15");
    return _i_cuse(result , "result", "15");
}

bool
getsub(arg, sub)
	char*	arg;
	char*	sub;
{
  _i_function("getsub");
  _i_node("0");
  _i_def(arg , "arg", "0");
  _i_def(sub , "sub", "0");

  _i_node("1");
    int	makeres;
    _i_def(makeres , "makeres", "1");

    _i_node("2");
    makeres = makesub(_i_cuse(arg , "arg", "2"), 0, _i_cuse(ENDSTR , "ENDSTR", "2","global"), _i_cuse(sub , "sub", "2"));
    _i_def(makeres , "makeres", "2");

    _i_node("3");
    return (_i_cuse(makeres , "makeres", "3") > 0);
}

void subline();

 bool
locate(c, pat, offset)
	character	c;
	char *	pat;
	int	offset;
{
  _i_function("locate");
  _i_node("0");
  _i_def(c , "c", "0");
  _i_def(pat , "pat", "0");
  _i_def(offset , "offset", "0");

  _i_node("1");
    int	i;
    bool flag;
    _i_def(i , "i", "1");
    _i_def(flag , "flag", "1");
    _i_node("2");
    flag = false;
    _i_def(flag , "flag", "2");
    _i_node("3");
    i = _i_cuse(offset , "offset", "3") + _i_cuse(pat[_i_cuse(offset , "offset", "3")] , "pat", "3");
    _i_def(i , "i", "3");

    while (_i_node("4") && (_i_puse(i , "i") > _i_puse(offset , "offset")))
    {
      _i_loc("4", "5");
      	if (_i_node("5") && (_i_puse(c , "c") == _i_puse(pat[_i_cuse(i , "i", "5")] , "pat"))) {
          _i_loc("5", "6");
          _i_node("6");
      	    flag = true;
            _i_def(flag , "flag", "6");
            _i_node("7");
      	    i = _i_cuse(offset , "offset", "7");
            _i_def(i , "i", "7");
      	} else{
          _i_loc("5", "8");
          _i_node("8");
      	    i = _i_cuse(i , "i", "8") - 1;
            _i_def(i , "i", "8");
        }
    }
    _i_loc("4", "9");
    _i_node("9");
    return _i_cuse(flag , "flag", "9");
}

bool
omatch(lin, i, pat, j)
	char*	lin;
	int	*i;
	char*	pat;
	int	j;
{
    _i_function("omatch");
    _i_node("0");
    _i_def(lin , "lin", "0");
    _i_def(i , "i", "0");
    _i_def(pat , "pat", "0");
    _i_def(j , "j", "0");

    _i_node("1");
    char	advance;
    bool result;
    _i_def(advance , "advance", "1");
    _i_def(result , "result", "1");

    _i_node("2");
    advance = -1;
    _i_def(advance , "advance", "2");
    if (_i_node("3") && (_i_puse(lin[_i_cuse(*i , "i", "3")] , "lin") == _i_puse(ENDSTR , "ENDSTR", "global"))){
      _i_loc("3", "4");
      _i_node("4");
	     result = false;
       _i_def(result , "result", "4");
     }
    else
    {
      _i_loc("3", "5");

	     if (_i_node("5") && (!in_pat_set(_i_puse(pat[_i_cuse(j , "j", "5")] , "pat"))))
	      {
          _i_loc("5", "6");
          _i_node("6");
	         (void)fprintf(stdout, "in omatch: can't happen\n");
	          abort();
	      } else
	      {
          _i_loc("5", "7");

	         switch (pat[j])
	         {
      	     case LITCHAR:
                  _i_node("7");
                  _i_puse(pat[_i_cuse(j , "j", "7")],"pat");
                  _i_puse(LITCHAR , "LITCHAR","global");
                  _i_loc("7", "8");

            		 if (_i_node("8") && (_i_puse(lin[_i_cuse(*i , "i", "8")] , "lin") == _i_puse(pat[_i_cuse(j , "j", "8") + 1] , "pat"))){
                      _i_loc("8", "9");
                      _i_node("9");
              		    advance = 1;
                      _i_def( advance, "advance", "9");
                   }
      		   break ;
      	     case BOL:
                 _i_node("26");
                 _i_puse(pat[_i_cuse(j , "j", "26")],"pat");
                 _i_puse(BOL , "BOL","global");
                 _i_loc("26", "10");
            		 if (_i_node("10") && (_i_puse(*i , "i") == 0)){
                      _i_loc("10", "11");
                      _i_node("11");
              		    advance = 0;
                      _i_def(advance , "advance", "11");
                 }
      		   break ;
      	     case ANY:
                 _i_node("27");
                 _i_puse(pat[_i_cuse(j , "j", "27")],"pat");
                 _i_puse(ANY , "ANY","global");
                 _i_loc("27", "12");
            		 if (_i_node("12") && (_i_puse(lin[_i_cuse(*i , "i", "12")] , "lin") != _i_puse(NEWLINE , "NEWLINE","global"))){
                   _i_loc("12", "13");
                   _i_node("13");
            		     advance = 1;
                   _i_def( advance, "advance", "13");
                  }
      		   break ;
      	     case EOL:
                 _i_node("28");
                 _i_puse(pat[_i_cuse(j , "j", "28")],"pat");
                _i_puse(EOL , "EOL","global");
                _i_loc("28", "14");

            		 if (_i_node("14") && (_i_puse(lin[_i_cuse(*i , "i", "14")] , "lin") == _i_puse(NEWLINE , "NEWLINE"))){
                    _i_loc("14", "15");
                    _i_node("15");
                    advance = 0;
                    _i_def(advance , "advance", "15");
                 }
        		 break ;
      	     case CCL:
                _i_node("29");
                _i_puse(pat[_i_cuse(j , "j", "29")],"pat");
                _i_puse(CCL , "CCL","global");
                _i_loc("29", "16");


          		 if (_i_node("16") && (locate(_i_puse(lin[_i_cuse(*i , "i", "16")] , "lin"), _i_puse(pat , "pat"), _i_puse(j , "j") + 1))){
                  _i_loc("16", "17");
                  _i_node("17");
          		    advance = 1;
                  _i_def(advance , "advance", "17");
                }
          	 break ;
      	     case NCCL:
             _i_node("30");
             _i_puse(pat[_i_cuse(j , "j", "30")],"pat");
             _i_puse(NCCL , "NCCL","global");
             _i_loc("30", "18");
          		 if (_i_node("18") && ((_i_puse(lin[_i_cuse(*i , "i", "18")] , "lin") != _i_puse(NEWLINE , "NEWLINE","global")) && (!locate(_i_puse(lin[_i_cuse(*i , "i", "18")] , "lin"), _i_puse(pat , "pat"), _i_puse(j , "j")+1))) ){
                  _i_loc("18", "19");
                  _i_node("19");
                   advance = 1;
                   _i_def(advance , "advance", "19");
               }
        		 break;
      	     default:
                 _i_node("31");
                 _i_puse(pat[_i_cuse(j , "j", "31")],"pat");
                _i_loc("31", "20");
                _i_node("20");
      		      Caseerror(_i_cuse(pat[_i_cuse(j , "j", "20")] , "pat", "20"));
      	     };
	      }
    }

    if (_i_node("21") && (_i_puse(advance , "advance") >= 0)){
      _i_loc("21", "22");
      _i_node("22");
    	*i = _i_cuse(*i , "i", "22") + _i_cuse(advance , "advance", "22");
      _i_def(i , "i", "22");
      _i_node("23");
    	result = true;
      _i_def(result , "result", "23");
    } else{
      _i_loc("21", "24");
      _i_node("24");
    	result = false;
      _i_def(result , "result", "24");
    }
    _i_node("25");
    return _i_cuse(result , "result", "25");
}


patsize(pat, n)
	char*	pat;
	int	n;
{
    _i_function("patsize");
    _i_node("0");
    _i_def(pat , "pat", "0");
    _i_def(n , "n", "0");
    _i_node("1");
    int size;
    _i_def(size , "size", "1");
    if (_i_node("2") && (!in_pat_set(_i_puse(pat[_i_cuse(n , "n", "2")] , "pat")))) {
      _i_loc("2", "3");
      _i_node("3");
      (void)fprintf(stdout, "in patsize: can't happen\n");
    	abort();
    } else{
      _i_loc("2", "4");

    	switch (pat[n])
    	{
    	case LITCHAR:
        _i_node("4");
        _i_puse(pat[_i_cuse(n , "n", "4")],"pat");
        _i_puse(LITCHAR , "LITCHAR","global");
        _i_loc("4", "5");
        _i_node("5");

        size = 2;
        _i_def(size , "size", "5");

      break;

    	case BOL:
      _i_node("6");
      _i_puse(pat[_i_cuse(n , "n", "6")],"pat");
      _i_puse(BOL , "BOL","global");
      _i_loc("6", "7");
      _i_node("7");
      size = 1;
      _i_def(size , "size", "7");
      break;
      case EOL:
      _i_node("8");
      _i_puse(pat[_i_cuse(n , "n", "8")],"pat");
      _i_puse(EOL , "EOL","global");
      _i_loc("8", "9");
      _i_node("9");
      size = 1;
      _i_def(size , "size", "9");

      break;
      case ANY:
      _i_node("10");
      _i_puse(pat[_i_cuse(n , "n", "10")],"pat");
      _i_puse(ANY , "ANY","global");
      _i_loc("10", "11");
      _i_node("11");
      size = 1;
      _i_def(size , "size", "11");

    	break;
    	case CCL:
      _i_node("12");
      _i_puse(pat[_i_cuse(n , "n", "12")],"pat");
      _i_puse(CCL , "CCL","global");
      _i_loc("12", "13");
      _i_node("13");
      size = _i_cuse(pat[_i_cuse(n , "n", "13") + 1] , "pat", "13") + 2;
      _i_def(size , "size", "13");

      case NCCL:
      _i_node("14");
      _i_puse(pat[_i_cuse(n , "n", "14")],"pat");
      _i_puse(NCCL , "NCCL","global");
      _i_loc("14", "15");
      _i_node("15");
      size = _i_cuse(pat[_i_cuse(n , "n", "15") + 1] , "pat", "15") + 2;
      _i_def(size , "size", "15");
    	break ;
    	case CLOSURE:
      _i_node("16");
      _i_puse(pat[_i_cuse(n , "n", "16")],"pat");
      _i_puse(CLOSURE , "CLOSURE","global");
      _i_loc("16", "17");
      _i_node("17");
	    size = _i_cuse(CLOSIZE , "CLOSIZE", "17","global");
      _i_def( size, "size", "17");
	    break ;
    	default:
      _i_node("18");
      _i_puse(pat[_i_cuse(n , "n", "18")],"pat");
      _i_puse(CLOSURE , "CLOSURE","global");
      _i_loc("18", "19");
      _i_node("20");
    	    Caseerror(_i_cuse(pat[_i_cuse(n , "n", "20")] , "pat", "20"));
    	}
    }
    _i_node("21");
    return _i_cuse(size , "size", "21");
}

int
amatch(lin, offset, pat, j)
	char*	lin;
	int	offset;
	char*	pat;
	int	j;
{
    _i_function("amatch");
    _i_node("0");
    _i_def(lin , "lin", "0");
    _i_def(offset , "offset", "0");
    _i_def(pat , "pat", "0");
    _i_def(j , "j", "0");
    _i_node("1");
    int	i, k;
    bool	result, done;
    _i_def(i , "i", "1");
    _i_def(k , "k", "1");
    _i_def(result , "result", "1");
    _i_def(done , "done", "1");


    _i_node("2");
    done = false;
    while (_i_node("3") &&((!_i_puse(done , "done")) && (_i_puse(pat[_i_cuse(j , "j", "3")] , "pat") != _i_puse(ENDSTR , "ENDSTR")))){
      _i_loc("3", "4");

      	if (_i_node("4") &&(_i_puse(pat[_i_cuse(j , "j", "4")] , "pat") == _i_puse(CLOSURE , "CLOSURE","global"))) {
            _i_loc("4", "5");
            _i_node("5");
            j = _i_cuse(j , "j", "5") + patsize(_i_cuse(pat , "pat", "5"), _i_cuse(j , "j", "5"));
            _i_def(j , "j", "5");
            _i_node("6");
      	    i = _i_cuse(offset , "offset", "6");
            _i_def(i , "i", "6");

      	    while (_i_node("7") &&((!_i_puse(done , "done")) && (_i_puse(lin[_i_cuse(i , "i", "7")] , "lin") != _i_puse(ENDSTR , "ENDSTR")))) {
                _i_loc("7", "8");
                _i_node("8");
            		result = omatch(_i_cuse(lin , "lin", "8"), _i_cuse( &i, "i", "8"), _i_cuse(pat , "pat", "8"), _i_cuse(j , "j", "8"));
                _i_def(result , "result", "8");
                if (_i_node("9") && (!_i_puse(result , "result"))){
                  _i_loc("9", "10");
                  _i_node("10");
            		   done = true;
                  _i_def(done , "done", "10");
                }
                else{
                  _i_loc("9", "11");
                  _i_node("11");
                }

      	    }
            _i_loc("7", "12");
            _i_node("12");
      	    done = false;
            _i_def(done , "done", "12");

      	    while (_i_node("13") && ((!_i_puse(done , "done")) && (_i_puse(i , "i") >= _i_puse(offset , "offset")))) {
                _i_loc("13", "14");
                _i_node("14");
            		k = amatch(_i_cuse(lin , "lin", "14"), _i_cuse(i , "i", "14"), _i_cuse(pat , "pat", "14"), _i_cuse(j , "j", "14") + patsize(_i_cuse(pat , "pat", "14"), _i_cuse(j , "j", "14")));
                _i_def(k , "k", "14");
                if (_i_node("15") && (_i_puse(k , "k") >= 0)){
                    _i_loc("15", "16");
                    _i_node("16");
                    done = true;
                    _i_def(done , "done", "16");
                  }
            		else{
                    _i_loc("15", "17");
                    _i_node("17");
            		    i = _i_cuse(i , "i", "17") - 1;
                    _i_def(i , "i", "17");
                  }
      	    }
            _i_loc("13", "18");
            _i_node("18");
      	    offset = _i_cuse(k , "k", "18");
            _i_def(offset , "offset", "18");
      	    done = true;
            _i_node("19");
            _i_def(done , "done", "19");
      	} else {
            _i_loc("4", "20");
            _i_node("20");
      	    result = omatch(_i_cuse(lin , "lin", "20"), _i_cuse(&offset , "offset", "20"), _i_cuse(pat , "pat", "20"), _i_cuse(j , "j", "20"));
            _i_def(result , "result", "20");
      	    if (_i_node("21") &&(!_i_puse(result , "result"))) {
              _i_loc("21", "22");
              _i_node("22");
          		offset = -1;
              _i_def(offset , "offset", "22");
              _i_node("23");
          		done = true;
              _i_def(done , "done", "23");
      	    } else{
              _i_loc("21", "24");
              _i_node("24");
        		  j = _i_cuse(j , "j", "24") + patsize(_i_cuse(pat , "pat", "24"), _i_cuse(j , "j", "24"));
              _i_def(j , "j", "24");
            }
      	}
      }
      _i_loc("3", "25");
      _i_node("25");
     return _i_cuse(offset , "offset", "25");
}

void
putsub(lin, s1, s2, sub)
  char *	lin;
  int	s1, s2;
  char *	sub;
{
  _i_function("putsub");
  _i_node("0");
  _i_def(lin , "lin", "0");
  _i_def(s1 , "s1", "0");
  _i_def(s2 , "s2", "0");
  _i_def(sub , "sub", "0");

  _i_node("1");
    int	i;
    int	j;
    _i_def(i , "i", "1");
    _i_def(j , "j", "1");

    _i_node("2");
    i = 0;
    _i_def(i , "i", "2");
    while (_i_node("3") && (_i_puse(sub[_i_cuse(i , "i", "3")] , "sub") != _i_puse(ENDSTR , "ENDSTR","global"))) {
        _i_loc("3", "4");

        if (  _i_node("4") && (_i_puse(sub[_i_cuse(i , "i", "4")] , "sub") == _i_puse(DITTO , "DITTO","global"))){
          _i_loc("4", "5");

          for (_i_node("5"),j = _i_cuse(s1 , "s1", "5"),_i_def(j , "j", "5");_i_node("6") && (_i_puse(j , "j") < _i_puse(s2 , "s2"));_i_node("8"),  _i_def(_i_cuse(j++ , "j", "8") , "j", "8"))
    	    {
              _i_loc("6", "7");
              _i_node("7");
    		        fputc(_i_cuse(lin[_i_cuse(j , "j", "7")] , "lin", "7"),stdout);
          }
          _i_loc("6", "9");
          _i_node("9");

        }
	       else
        	{
            _i_loc("4", "10");
            _i_node("10");
        	    fputc(_i_cuse(sub[_i_cuse(i , "i", "10")] , "sub", "10"),stdout);
        	}
        _i_node("11");
      	i = _i_cuse(i , "i", "11") + 1;
        _i_def(i , "i", "11");
    }
    _i_loc("3", "12");
    _i_node("12");
}

void
subline(lin, pat, sub)
 char	*lin;
 char   *pat;
 char   *sub;
{
  _i_function("subline");
  _i_node("0");

_i_def(lin , "lin", "0");
_i_def( pat , " pat", "0");
_i_def(sub , "sub", "0");

  _i_node("1");
	int	i, lastm, m;
_i_def(i , "i", "1");
_i_def(lastm , "lastm", "1");
_i_def(m , "m", "1");
_i_node("2");

	lastm = -1;
  _i_def(lastm , "lastm", "2");

  _i_node("3");
	i = 0;
  _i_def(i , "i", "3");
	while (_i_node("4") && (_i_puse(lin[_i_cuse(i , "i", "4")] , "lin") != _i_puse(ENDSTR , "ENDSTR","global")))
	{
      _i_loc("4", "5");
      _i_node("5");
	    m = amatch(_i_cuse(lin , "lin", "5"), _i_cuse(i , "i", "5"), _i_cuse(pat , "pat", "5"), 0);
      _i_def(m , "m", "5");
	    if (_i_node("6") && ((_i_puse(m , "m") >= 0) && (_i_puse(lastm , "lastm") != _i_puse(m , "m")))) {
        _i_loc("6", "7");
        _i_node("7");
		      putsub(_i_cuse(lin , "lin", "7"), _i_cuse(i , "i", "7"), _i_cuse(m , "m", "7"), _i_cuse(sub , "sub", "7"));
          _i_node("8");
          lastm = _i_cuse(m , "m", "8");
          _i_def(lastm , "lastm", "8");
	    }else{
        _i_loc("6", "9");
        _i_node("9");
      }

	    if (_i_node("10") && ((_i_puse(m , "m") == -1) || (_i_puse(m , "m") == i))) {
        _i_loc("10", "11");
        _i_node("11");
    		fputc(_i_cuse(lin[_i_cuse(i , "i", "11")] , "lin", "11"),stdout);
        _i_node("12");
    		i = _i_cuse(i , "i", "12") + 1;
        _i_def(i , "i", "12");
	    } else{
        _i_loc("10", "13");
    		i = _i_cuse(m , "m", "13");
        _i_def(i , "i", "13");
      }
	}
  _i_loc("4", "14");
  _i_node("14");

}

 void
change(pat, sub)
char *pat, *sub;
{
  _i_function("change");
  _i_node("0");
  _i_def(pat , "pat", "0");
  _i_def(sub , "sub", "0");

  _i_node("1");
    string  line;
    bool result;
  _i_def(line , "line", "1");
  _i_def(result , "result", "1");
  _i_node("2");

    result = getline(_i_cuse(line , "line", "2"), _i_cuse(MAXSTR , "MAXSTR", "2","global"));
    _i_def(result , "result", "2");
    while (_i_node("3") && (_i_puse(result , "result"))) {
      _i_loc("3", "4");
      _i_node("4");
    	subline(_i_cuse(line , "line", "4"), _i_cuse(pat , "pat", "4"), _i_cuse(sub , "sub", "4"));
      _i_node("5");
    	result = getline(_i_cuse(line , "line", "5"), _i_cuse(MAXSTR , "MAXSTR", "5","global"));
      _i_def(result , "result", "5");
    }
    _i_loc("3", "6");
    _i_node("6");

}

void global_sets(){
  _i_function("global");
  _i_node("0");
  _i_def(MAXSTR,"MAXSTR","0");
  _i_def(MAXPAT,"MAXPAT","0");
  _i_def(ENDSTR,"ENDSTR","0");
  _i_def(ESCAPE,"ESCAPE","0");
  _i_def(CLOSURE,"CLOSURE","0");
  _i_def(BOL,"BOL","0");
  _i_def(EOL,"EOL","0");
  _i_def(ANY,"ANY","0");
  _i_def(CCL,"CCL","0");
  _i_def(CCLEND,"CCLEND","0");
  _i_def(NEGATE,"NEGATE","0");
  _i_def(NCCL,"NCCL","0");
  _i_def(LITCHAR,"LITCHAR","0");
  _i_def(DITTO,"DITTO","0");
  _i_def(DASH,"DASH","0");
  _i_def(TAB,"TAB","0");
  _i_def(NEWLINE,"NEWLINE","0");
  _i_def(CLOSIZE,"CLOSIZE","0");
}
main(argc, argv)
int	argc;
char	*argv[];
{

global_sets();

  _i_function("main");
  _i_node("0");
  _i_def(argc , "argc", "0");
  _i_def(argv , "argv", "0");

  _i_node("1");
   string pat, sub;
   bool result;
  _i_def(pat , "pat", "1");
  _i_def(sub , "sub", "1");
  _i_def(result , "result", "1");
   if (_i_node("2") && (_i_puse(argc , "argc") < 2))
   {
      _i_loc("2", "3");
      _i_node("3");
       (void)fprintf(stdout, "usage: change from [to]\n");
       exit(1);
   }else{
     _i_loc("2", "4");
     _i_node("4");
   }
   _i_node("5");
   result = getpat(_i_cuse(argv[1] , "argv", "5"), _i_cuse( pat, "pat", "5"));
   _i_def(result , "result", "5");

   if (_i_node("6") && (!_i_puse(result , "result")))
   {
      _i_loc("6", "7");
      _i_node("7");
       (void)fprintf(stdout, "change: illegal \"from\" pattern\n");
       exit(2);
   }else{
     _i_loc("6", "8");
     _i_node("8");
   }

   if (_i_node("9") && (_i_puse( argc, "argc") >= 3))
   {
     _i_loc("9", "10");
     _i_node("10");
       result = getsub(_i_cuse(argv[2] , "argv", "10"), _i_cuse(sub , "sub", "10"));
       _i_def(result , "result", "10");
       if (_i_node("11") &&(!_i_puse(result , "result")))
       {
           _i_loc("11", "12");
           _i_node("12");
      	   (void)fprintf(stdout, "change: illegal \"to\" string\n");
      	   exit(3);
         }else{
           _i_loc("11", "13");
           _i_node("13");
         }
   } else
   {
    _i_loc("9", "14");
    _i_node("14");
       sub[0] = '\0';
       _i_def(sub , "sub", "14");
   }
   _i_node("15");

   change(_i_cuse(pat , "pat", "15"), _i_cuse(sub , "sub", "15"));
   return 0;
}

void
Caseerror(n)
	int	n;
{
  _i_function("Caseerror");
  _i_node("0");
  _i_def(n , "n", "0");
  _i_node("1");
	(void)fprintf(stdout, "Missing case limb: line %d\n", _i_cuse(n , "n", "1"));
	exit(4);
}
