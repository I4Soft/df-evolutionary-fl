

# include <ctype.h>

# define START  5
# define TRUE  1
# define FALSE 0

typedef int BOOLEAN;
typedef char *string;

# include <stdio.h>
# include "tokens.h"


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


static token numeric_case();
static token error_or_eof_case();
static int check_delimiter();
static int keyword(int state);
static int special(int state);
static skip(character_stream stream_ptr);
static int constant(int state,char token_str[],int token_ind);
static int next_state();
static get_actual_token(char token_str[],int token_ind);


void global_sets(){
  _i_function("global");
  _i_node("0");
  _i_def(START , "START", "0");
  _i_def(TRUE , "TRUE", "0");
  _i_def(FALSE , "FALSE", "0");
  _i_def(EOTSTREAM , "EOTSTREAM", "0");
  _i_def(NUMERIC , "NUMERIC", "0");
  _i_def(IDENTIFIER , "IDENTIFIER", "0");
  _i_def(LAMBDA , "LAMBDA", "0");
  _i_def(AND , "AND", "0");
  _i_def(OR , "OR", "0");
  _i_def(IF , "IF", "0");
  _i_def(XOR , "XOR", "0");
  _i_def(LPAREN , "LPAREN", "0");
  _i_def(RPAREN , "RPAREN", "0");
  _i_def(LSQUARE , "LSQUARE", "0");
  _i_def(RSQUARE , "RSQUARE", "0");
  _i_def(QUOTE , "QUOTE", "0");
  _i_def(BQUOTE , "BQUOTE", "0");
  _i_def(COMMA , "COMMA", "0");
  _i_def(EQUALGREATER , "EQUALGREATER", "0");
  _i_def(STRING_CONSTANT , "STRING_CONSTANT", "0");
  _i_def(CHARACTER_CONSTANT , "CHARACTER_CONSTANT", "0");
  _i_def(ERROR , "ERROR", "0");
  _i_def(default1 , "default1", "0");
  _i_def(base , "base", "0");
  _i_def(next , "next", "0");
  _i_def(check , "check", "0");

}
main(argc,argv)
int argc;
char *argv[];
{
  global_sets();
  _i_function("main");
  _i_node("0");
  _i_def(argc , "argc", "0");
  _i_def(argv , "argv", "0");

  _i_node("1");
      token token_ptr;
      token_stream stream_ptr;
      _i_def(token_ptr , "token_ptr", "1");
      _i_def(stream_ptr , "stream_ptr", "1");

      if(_i_node("2") && (_i_puse(argc , "2")>2))
      {
        _i_loc("2", "3");
        _i_node("3");
          fprintf(stdout, "The format is print_tokens filename(optional)\n");
          exit(1);
      }else{
        _i_loc("2", "4");
        _i_node("4");
      }
      _i_node("5");
      stream_ptr=open_token_stream(_i_cuse(argv[1] , "argv", "5"));
      _i_def(stream_ptr , "stream_ptr", "5");

      while(_i_node("6") && (!is_eof_token((_i_puse(_i_def(token_ptr=get_token(_i_cuse(stream_ptr , "stream_ptr", "6")) , "token_ptr", "6") , "token_ptr"))))){
          _i_loc("6", "7");
          _i_node("7");
          print_token(_i_cuse(token_ptr , "token_ptr", "7"));
        }
        _i_loc("6", "8");
        _i_node("8");
      print_token(_i_cuse(token_ptr , "token_ptr", "8"));
  exit(0);
}



/* *********************************************************************
       Function name : open_character_stream
       Input         : filename
       Output        : charactre stream.
       Exceptions    : If file name doesn't exists it will
                       exit from the program.
       Description   : The function first allocates the memory for
                       the structure and initilizes it. The constant
                       START gives the first character available in
                       the stream. It ckecks whether the filename is
                       empty string. If it is it assigns file pointer
                       to stdin else it opens the respective file as input.                   * ******************************************************************* */

character_stream open_character_stream(FILENAME)
string FILENAME;
{
      _i_function("open_character_stream");
      _i_node("0");
      _i_def(FILENAME , "FILENAME", "0");
      _i_node("1");
      character_stream stream_ptr;
      _i_def(stream_ptr , "stream_ptr", "1");

      _i_node("2");
      stream_ptr=(character_stream)malloc(sizeof(struct stream_type));
      _i_def(stream_ptr , "stream_ptr", "2");
      _i_node("3");
      stream_ptr->stream_ind=_i_cuse(START , "START", "3","global");
      _i_def(stream_ptr , "stream_ptr", "3");
      _i_node("4");
      stream_ptr->stream[_i_cuse(START , "START", "4","global")]='\0';
      _i_def(stream_ptr , "stream_ptr", "4");

      if(_i_node("5") && (_i_cuse(FILENAME, "FILENAME", "5") == NULL)){
        _i_loc("5", "6");
        _i_node("6");
          stream_ptr->fp=stdin;
          _i_def(stream_ptr , "stream_ptr", "6");
        }
      else{
        _i_loc("5", "7");
        _i_node("7");
         if(_i_node("8") && ((_i_puse( _i_def(stream_ptr->fp=fopen(_i_cuse(FILENAME , "FILENAME", "8"),"r"), "stream_ptr", "8"), "stream_ptr")==NULL)))
           {
             _i_loc("8", "9");
             _i_node("9");
               fprintf(stdout, "The file %s doesn't exists\n",_i_cuse(FILENAME , "FILENAME", "9"));
               exit(0);
           }
           else{
             _i_loc("8", "10");
             _i_node("10");
           }
         }
        _i_node("11");
      return(_i_cuse(stream_ptr , "stream_ptr", "11"));
}

/* *********************************************************************
   Function name : get_char
   Input         : charcter_stream.
   Output        : character.
   Exceptions    : None.
   Description   : This function takes character_stream type variable
                   as input and returns one character. If the stream is
                   empty then it reads the next line from the file and
                   returns the character.
 * ****************************************************************** */

CHARACTER get_char(stream_ptr)
character_stream stream_ptr;
{
  _i_function("get_char");
  _i_node("0");
  _i_def(stream_ptr , "stream_ptr", "0");

      if(_i_node("1") && (_i_puse(stream_ptr->stream[_i_cuse(stream_ptr->stream_ind , "stream_ptr", "1")] , "stream_ptr") == '\0'))
      {
        _i_loc("1", "2");

              if(_i_node("2") && (_i_puse( _i_def(fgets(stream_ptr->stream+_i_cuse(START , "START", "2","global"),80-_i_cuse(START , "START", "2","global"),_i_cuse(stream_ptr->fp , "stream_ptr", "2")) , "stream_ptr", "2") , "stream_ptr") == NULL)){/* Fix bug: add -START - hf*/
                  _i_loc("2", "3");
                  _i_node("3");
                    stream_ptr->stream[_i_cuse(START , "START", "3","global")]=EOF;
                    _i_def(stream_ptr , "stream_ptr", "3");
              }else{
                _i_loc("2", "4");
                _i_node("4");
              }
              _i_node("5");
              stream_ptr->stream_ind=_i_cuse(START , "START", "5","global");
              _i_def(stream_ptr , "stream_ptr", "5");
      }else{
        _i_loc("1", "6");
        _i_node("6");
      }
      _i_node("7");
      return(_i_cuse(stream_ptr->stream[_i_def(_i_cuse((stream_ptr->stream_ind)++ , "stream_ptr", "7") , "stream_ptr", "7")] , "stream_ptr", "7"));
}

/* *******************************************************************
   Function name : is_end_of_character_stream.
   Input         : character_stream.
   Output        : Boolean value.
   Description   : This function checks whether it is end of character
                   stream or not. It returns BOOLEANvariable which is
                   true or false. The function checks whether the last
                   read character is end file character or not and
                   returns the value according to it.
 * ****************************************************************** */

BOOLEAN is_end_of_character_stream(stream_ptr)
character_stream stream_ptr;
{
  _i_function("is_end_of_character_stream");
  _i_node("0");
  _i_def(stream_ptr , "stream_ptr", "0");
      if(_i_node("1") && (_i_puse(stream_ptr->stream[_i_cuse(stream_ptr->stream_ind , "stream_ptr", "1")-1] , "stream_ptr") == EOF)){
        _i_loc("1", "2");
        _i_node("2");
            return(_i_cuse(TRUE , "TRUE", "2","global"));
      }
      else{
        _i_loc("1", "3");
        _i_node("3");
          return(_i_cuse(FALSE , "FALSE", "3","global"));
      }
}

/* *********************************************************************
   Function name : unget_char
   Input         : character,character_stream.
   Output        : void.
   Description   : This function adds the character ch to the stream.
                   This is accomplished by decrementing the stream_ind
                   and storing it in the stream. If it is not possible
                   to unget the character then it returns
 * ******************************************************************* */

unget_char(ch,stream_ptr)
CHARACTER ch;
character_stream stream_ptr;
{
  _i_function("unget_char");
  _i_node("0");
  _i_def(ch , "ch", "0");
  _i_def(stream_ptr , "stream_ptr", "0");
      if(_i_node("1") && (_i_puse(stream_ptr->stream_ind , "stream_ptr") == 0)){
        _i_loc("1", "2");
        _i_node("2");
          return;
        }
      else{
        _i_loc("1", "3");
        _i_node("3");
          stream_ptr->stream[ _i_cuse(_i_def(_i_cuse(--(stream_ptr->stream_ind), "stream_ptr", "3"), "stream_ptr", "3") , "stream_ptr", "3")]=_i_cuse(ch , "ch", "3");
          _i_def(stream_ptr , "stream_ptr", "3");
        }
        _i_node("4");
      return;
}


/* *******************************************************************
   Function name : open_token_stream
   Input         : filename
   Output        : token_stream
   Exceptions    : Exits if the file specified by filename not found.
   Description   : This function takes filename as input and opens the
                   token_stream which is nothing but the character stream.
                   This function allocates the memory for token_stream
                   and calls open_character_stream to open the file as
                   input. This function returns the token_stream.
 * ****************************************************************** */

token_stream open_token_stream(FILENAME)
string FILENAME;
{
  _i_function("open_token_stream");
  _i_node("0");
  _i_def(FILENAME , "FILENAME", "0");
  _i_node("1");
    token_stream token_ptr;
    _i_node("2");
    token_ptr=(token_stream)malloc(sizeof(struct token_stream_type));
    _i_def(token_ptr , "token_ptr", "2");

    _i_node("3");
    token_ptr->ch_stream=open_character_stream(_i_cuse(FILENAME , "FILENAME", "3"));/* Get character
                                                             stream  */
    _i_def(token_ptr , "token_ptr", "3");
    _i_node("4");
    return(_i_cuse(token_ptr , "token_ptr", "4"));
}

/* ********************************************************************
   Function name : get_token
   Input         : token_stream
   Output        : token
   Exceptions    : none.
   Description   : This function returns the next token from the
                   token_stream.The type of token is integer and specifies
                   only the type of the token. DFA is used for finding the
                   next token. cu_state is initialized to zero and charcter
                   are read until the the is the final state and it
                   returns the token type.
* ******************************************************************* */

token get_token(tstream_ptr)
token_stream tstream_ptr;
{
  _i_function("get_token");
  _i_node("0");
  _i_def(tstream_ptr , "tstream_ptr", "0");

  _i_node("1");
      char token_str[80]; /* This buffer stores the current token */
      int token_ind;      /* Index to the token_str  */
      token token_ptr;
      CHARACTER ch;
      int cu_state,next_st,token_found;
      token_ptr=(token)(malloc(sizeof(struct token_type)));
  _i_def(token_str , "token_str", "1");
  _i_def(token_ind , "token_ind", "1");
  _i_def(token_ptr , "token_ptr", "1");
  _i_def(ch , "ch", "1");
  _i_def(cu_state , "cu_state", "1");
  _i_def(next_st , "next_st", "1");
  _i_def(token_found , "token_found", "1");
  _i_def(token_ptr , "token_ptr", "1");

  _i_node("2");
      ch=get_char(_i_cuse(tstream_ptr->ch_stream , "tstream_ptr", "2"));
      _i_def(ch , "ch", "2");

      _i_node("3");
      cu_state=_i_cuse(_i_def(token_ind=_i_cuse(_i_def(token_found=0 , "token_found", "3") , "token_found", "3") , "token_ind", "3") , "token_ind", "3");
      _i_def(cu_state , "cu_state", "3");
      while(_i_node("4") && (!_i_puse(token_found , "token_found")))
      {
        _i_loc("4", "5");
        	  if(_i_node("5") &&(_i_puse(token_ind , "token_ind") < 80)) /* ADDED ERROR CHECK - hf */
        	  {
              _i_loc("5", "6");
              _i_node("6");
        	    token_str[_i_def(_i_cuse(token_ind++ , "token_ind", "6") , "token_ind", "6")]=_i_cuse(ch , "ch", "6");
              _i_def(token_str , "token_str", "6");
              _i_node("7");
        	    next_st=next_state(_i_cuse(cu_state , "cu_state", "7"),_i_cuse(ch , "ch", "7"));
              _i_def(next_st , "next_st", "7");
        	  }
        	  else
        	  {
              _i_loc("5", "8");
              _i_node("8");
        	      next_st = -1; /* - hf */
              _i_def(next_st , "next_st", "8");
        	  }

        	  if (_i_node("9") && (_i_puse(next_st , "next_st") == -1)) { /* ERROR or EOF case */
              _i_loc("9", "10");
              _i_node("10");
                return(error_or_eof_case(_i_cuse(tstream_ptr , "tstream_ptr", "10"),_i_cuse(token_ptr , "token_ptr", "10"),_i_cuse(cu_state , "cu_state", "10"),_i_cuse(token_str , "token_str", "10"),_i_cuse(token_ind , "token_ind", "10"),_i_cuse(ch , "ch", "10")));
        	  } else{
              _i_loc("9", "11");

              if (_i_node("11") && (_i_puse(next_st , "next_st") == -2)) {/* This is numeric case. */
                _i_loc("11", "12");
                _i_node("12");
                  return(numeric_case(_i_cuse(tstream_ptr , "tstream_ptr", "12"),_i_cuse(token_ptr , "token_ptr", "12"),_i_cuse(ch , "ch", "12"),_i_cuse(token_str , "token_str", "12"),_i_cuse(token_ind , "token_ind", "12")));
          	  } else{
                _i_loc("11", "13");
                  if (_i_node("13") &&(_i_puse(next_st , "next_st") == -3)) {/* This is the IDENTIFIER case */
                    _i_loc("13", "14");
                    _i_node("14");
                    token_ptr->token_id=_i_cuse(IDENTIFIER , "IDENTIFIER", "14","global");
                    _i_def(token_ptr , "token_ptr", "14");
                    _i_node("15");
            	      unget_char(_i_cuse(ch , "ch", "15"),_i_cuse( tstream_ptr->ch_stream, "tstream_ptr", "15"));
                    _i_node("16");
                     _i_def(_i_cuse(token_ind-- , "token_ind", "16") , "token_ind", "16");
                     _i_node("17");
            	      get_actual_token(_i_cuse(token_str , "token_str", "17"),_i_cuse(token_ind , "token_ind", "17"));

                    _i_node("18");
            	      strcpy(_i_cuse(token_ptr->token_string , "token_ptr", "18"),_i_cuse(token_str , "token_str", "18"));
                    _i_def(token_ptr , "token_ptr", "18");
                    _i_node("19");
            	      return(_i_cuse(token_ptr , "token_ptr", "19"));
            	  }else{
                  _i_loc("13", "20");
                  _i_node("20");
                }
              }
            }


        	  switch(next_st)
                    {
                         default :
                         _i_node("21");
                         _i_puse(next_st , "next_st");
                         _i_loc("21", "22");
                         _i_node("22");
                          break;
                         case 6  : /* These are all KEYWORD cases. */
                         case 9  :
                         case 11 :
                         case 13 :
                         case 16 :
                                   _i_node("21");

                                   _i_puse(next_st , "next_st");
                                   _i_loc("21", "23");
                                   _i_node("23");
                                   ch=get_char(_i_cuse(tstream_ptr->ch_stream , "tstream_ptr", "23"));
                                   _i_def(ch , "ch", "23");
                                   if(_i_node("24") && (check_delimiter(_i_puse(ch , "ch"))==_i_puse(TRUE , "TRUE","global")))
                                   {
                                     _i_loc("24", "25");
                                     _i_node("25");
                                         token_ptr->token_id=keyword(_i_cuse(next_st , "next_st", "25"));
                                         _i_def(token_ptr , "token_ptr", "25");
                                         _i_node("26");
                                         unget_char(_i_cuse(ch , "ch", "26"),_i_cuse( tstream_ptr->ch_stream, "tstream_ptr", "26"));
                                         _i_node("27");
                                         token_ptr->token_string[0]='\0';
                                         _i_def(token_ptr , "token_ptr", "27");
                                         _i_node("28");
                                         return(_i_cuse(token_ptr , "token_ptr", "28"));
                                   }else{
                                     _i_loc("24", "29");
                                     _i_node("29");
                                   }
                                   _i_node("30");
                                   unget_char(_i_cuse(ch , "ch", "30"),_i_cuse(tstream_ptr->ch_stream , "tstream_ptr", "30"));
                                   break;
                         case 19 : /* These are all special SPECIAL character */
                         case 20 : /* cases */
                         case 21 :
                         case 22 :
                         case 23 :
                         case 24 :
                         case 25 :
                         case 32 :
                                 _i_node("21");
                                 _i_puse(next_st , "next_st");
                                 _i_loc("21", "31");
                                 _i_node("31");
                                   token_ptr->token_id=special(_i_cuse(next_st , "next_st", "31"));
                                   _i_def(token_ptr , "token_ptr", "31");
                                   _i_node("32");
                                   token_ptr->token_string[0]='\0';
                                   _i_def(token_ptr , "token_ptr", "32");
                                   _i_node("33");
                                   return(_i_cuse(token_ptr , "token_ptr", "33"));
                         case 27 : /* These are constant cases */
                         case 29 :
                                   _i_node("21");
                                   _i_puse(next_st , "next_st");
                                   _i_loc("21", "34");
                                   _i_node("34");
                                   token_ptr->token_id=constant(_i_cuse(next_st , "next_st", "34"),_i_cuse(token_str , "token_str", "34"),_i_cuse(token_ind , "token_ind", "34"));
                                   _i_def(token_ptr , "token_ptr", "34");
                                   _i_node("35");
                                   get_actual_token(_i_cuse(token_str , "token_str", "35"),_i_cuse(token_ind , "token_ind", "35"));
                                   _i_node("36");
                                   strcpy(_i_cuse(token_ptr->token_string , "token_ptr", "36"),_i_cuse(token_str , "token_str", "36"));
                                   _i_def(token_ptr , "token_ptr", "36");
                                   _i_node("37");
                                   return(_i_cuse(token_ptr , "token_ptr", "37"));
                         case 30 :  /* This is COMMENT case */
                                   _i_node("21");
                                   _i_puse(next_st , "next_st");
                                   _i_loc("21", "34");
                                   _i_node("34");
                                   skip(_i_cuse(tstream_ptr->ch_stream , "tstream_ptr", "34"));
                                   _i_node("35");
                                   token_ind=_i_cuse(_i_def(next_st=0 , "next_st", "35") , "next_st", "35");
                                   _i_def(token_ind , "token_ind", "35");
                                   break;
                    }
                    _i_node("36");
                    cu_state=_i_cuse(next_st , "next_st", "36");
                    _i_def(cu_state , "cu_state", "36");
                    _i_node("37");
                    ch=get_char(_i_cuse(tstream_ptr->ch_stream , "tstream_ptr", "37"));
                    _i_def(ch , "ch", "37");
      }
      _i_loc("4", "38");
      _i_node("38");
}

/* ******************************************************************
   Function name : numeric_case
   Input         : tstream_ptr,token_ptr,ch,token_str,token_ind
   Output        : token_ptr;
   Exceptions    : none
   Description   : It checks for the delimiter, if it is then it
                   forms numeric token else forms error token.
 * ****************************************************************** */

static token numeric_case(tstream_ptr,token_ptr,ch,token_str,token_ind)
token_stream tstream_ptr;
token token_ptr;
char ch,token_str[];
int token_ind;
{
    _i_function("numeric_case");
    _i_node("0");
    _i_def(tstream_ptr , "tstream_ptr", "0");
    _i_def(token_ptr , "token_ptr", "0");
    _i_def(ch , "ch", "0");
    _i_def(token_str , "token_str", "0");
    _i_def(token_ind , "token_ind", "0");

        if(_i_node("1") && (check_delimiter(_i_puse(ch , "ch"))!= _i_puse(TRUE , "TRUE","global")))
        {   /* Error case */
          _i_loc("1", "2");
          _i_node("2");
            token_ptr->token_id=_i_cuse(ERROR , "ERROR", "2","global");
            _i_def(token_ptr , "token_ptr", "2");
            while(_i_node("3") && (check_delimiter(_i_puse(ch , "ch"))==_i_puse(FALSE , "FALSE","global"))){
                _i_loc("3", "4");

            		if(_i_node("4") && (_i_cuse(token_ind , "token_ind", "4") >= 80)){
                  _i_loc("4", "5");
                  _i_node("5");
                  break; /* Added protection - hf */
                }else{
                  _i_loc("4", "6");
                  _i_node("6");
                }
                _i_node("7");
            		token_str[ _i_def(_i_cuse(token_ind++ , "token_ind", "7") , "token_ind", "7")]=_i_cuse(_i_def(ch=get_char(_i_cuse(tstream_ptr->ch_stream , "tstream_ptr", "7")) , "ch", "7") , "ch", "7");
                _i_def(token_str , "token_str", "7");
             }
             _i_loc("3", "8");
             _i_node("8");
            unget_char(_i_cuse(ch , "ch", "8"),_i_cuse(tstream_ptr->ch_stream , "tstream_ptr", "8"));
            _i_node("9");
            _i_def(_i_cuse(token_ind-- , "token_ind", "9") , "token_ind", "9");

            _i_node("10");
            get_actual_token(_i_cuse(token_str , "token_str", "10"),_i_cuse(token_ind , "token_ind", "10"));
            _i_node("11");
            strcpy(_i_cuse(token_ptr->token_string , "token_ptr", "11"),_i_cuse(token_str , "token_str", "11"));
            _i_def(token_ptr , "token_ptr", "11");
            _i_node("12");
            return(_i_cuse(token_ptr , "token_ptr", "12"));
        }else{
          _i_loc("1", "13");
          _i_node("13");
        }
        _i_node("14");
        token_ptr->token_id=_i_cuse(NUMERIC , "NUMERIC", "14","global"); /* Numeric case */
        _i_def(token_ptr , "token_ptr", "14");

        _i_node("15");
        unget_char(_i_cuse(ch , "ch", "15"),_i_cuse(tstream_ptr->ch_stream , "tstream_ptr", "15"));
        _i_node("16");
        _i_def(_i_cuse(token_ind-- , "token_ind", "16") , "token_ind", "16");
        _i_node("17");
        get_actual_token(_i_cuse(token_str , "token_str", "17"),_i_cuse(token_ind , "token_ind", "17"));
        _i_node("18");
        strcpy(_i_cuse(token_ptr->token_string , "token_ptr", "18"),_i_cuse(token_str , "token_str", "18"));
        _i_def(token_ptr , "token_ptr", "18");
        _i_node("19");
        return(_i_cuse(token_ptr , "token_ptr", "19"));
}

/* *****************************************************************
   Function name : error_or_eof_case
   Input         : tstream_ptr,token_ptr,cu_state,token_str,token_ind,ch
   Output        : token_ptr
   Exceptions    : none
   Description   : This function checks whether it is EOF or not.
                   If it is it returns EOF token else returns ERROR
                   token.
 * *****************************************************************/

static token error_or_eof_case(tstream_ptr,token_ptr,cu_state,token_str,token_ind,ch)
token_stream tstream_ptr;
token token_ptr;
int cu_state,token_ind;
char token_str[],ch;
{
  _i_function("error_or_eof_case");
  _i_node("0");
  _i_def(tstream_ptr , "tstream_ptr", "0");
  _i_def(token_ptr , "token_ptr", "0");
  _i_def(cu_state , "cu_state", "0");
  _i_def(token_str , "token_str", "0");
  _i_def(token_ind , "token_ind", "0");
  _i_def(ch , "ch", "0");

      if(_i_node("1") && (is_end_of_character_stream(_i_puse(tstream_ptr->ch_stream , "tstream_ptr"))))
      {
        _i_loc("1", "2");
        _i_node("2");
            token_ptr->token_id = _i_cuse(EOTSTREAM , "EOTSTREAM", "2","global");
        _i_def(token_ptr , "token_ptr", "2");
        _i_node("3");
            token_ptr->token_string[0]='\0';
        _i_def(token_ptr , "token_ptr", "3");
        _i_node("4");
            return(_i_cuse(token_ptr , "token_ptr", "4"));
      }else{
        _i_loc("1", "5");
        _i_node("5");
      }

      if(_i_node("6") && (_i_puse(cu_state , "cu_state") !=0))
      {
        _i_loc("6", "7");
        _i_node("7");
        unget_char(_i_cuse(ch , "ch", "7"),_i_cuse(tstream_ptr->ch_stream , "tstream_ptr", "7"));
        _i_node("8");
        _i_def(_i_cuse(token_ind-- , "token_ind", "8") , "token_ind", "8");
      }else{
        _i_loc("6", "9");
        _i_node("9");

      }
      _i_node("10");
      token_ptr->token_id=_i_cuse(ERROR , "ERROR", "10","global");
      _i_def(token_ptr , "token_ptr", "10");
      _i_node("11");
      get_actual_token(_i_cuse(token_str , "token_str", "11"),_i_cuse(token_ind , "token_ind", "11"));
      _i_node("12");
      strcpy(_i_cuse(token_ptr->token_string , "token_ptr", "12"),_i_cuse(token_str , "token_str", "12"));
      _i_def(token_ptr , "token_ptr", "12");
      _i_node("13");
      return(_i_cuse(token_ptr , "token_ptr", "13"));
}

/* *********************************************************************
   Function name : check_delimiter
   Input         : character
   Output        : boolean
   Exceptions    : none.
   Description   : This function checks for the delimiter. If ch is not
                   alphabet and non numeric then it returns TRUE else
                   it returns FALSE.
 * ******************************************************************* */

static int check_delimiter(ch)
char ch;
{
  _i_function("check_delimiter");
  _i_node("0");
  _i_def(ch , "ch", "0");

      if(_i_node("1") && (!isalpha(_i_puse(ch , "ch")) && !isdigit(_i_puse(ch , "ch")))){ /* Check for digit and alpha */
        _i_loc("1", "2");
        _i_node("2");
          return(_i_cuse(TRUE , "TRUE", "2","global"));
      }else{
        _i_loc("1", "3");
        _i_node("3");
      }
      _i_node("4");
      return(_i_cuse(FALSE , "FALSE", "4","global"));
}

/* ********************************************************************
   Function name : keyword
   Input         : state of the DFA
   Output        : Keyword.
   Exceptions    : If the state doesn't represent a keyword it exits.
   Description   : According to the final state specified by state the
                   respective token_id is returned.
 * ***************************************************************** */

static int keyword(state)
int state;
{
    _i_function("keyword");
    _i_node("0");
    _i_def(state , "state", "0");

      switch(state)
      {   /* Return the respective macro for the Keyword. */
          case 6 :
          _i_node("1");
          _i_puse(state , "state");
          _i_loc("1", "2");
          _i_node("2");
          return(_i_cuse(LAMBDA , "LAMBDA", "2","global"));
          case 9 :
          _i_node("1");
          _i_puse(state , "state");
          _i_loc("1", "3");
          _i_node("3");
           return(_i_cuse(AND , "AND", "3","global"));
          case 11:
          _i_node("1");
          _i_puse(state , "state");
          _i_loc("1", "4");
          _i_node("4");
          return(_i_cuse(OR , "OR", "4","global"));
          case 13:
          _i_node("1");
          _i_puse(state , "state");
          _i_loc("1", "5");
          _i_node("5");
           return(_i_cuse(IF , "IF","5", "global"));
          case 16:
          _i_node("1");
          _i_puse(state , "state");
          _i_loc("1", "6");
          _i_node("6");
          return(_i_cuse(XOR , "XOR", "6","global"));
          default:
          _i_node("1");
          _i_puse(state , "state");
          _i_loc("1", "7");
          _i_node("7");
           fprintf(stdout, "error\n");
           break;
      }
      _i_node("8");
      exit(0);
}

/* ********************************************************************
   Function name : special
   Input         : The state of the DFA.
   Output        : special symbol.
   Exceptions    : if the state doesn't belong to a special character
                   it exits.
   Description   : This function returns the token_id according to the
                   final state given by state.
 * ****************************************************************** */

static int special(state)
int state;
{
  _i_function("special");
  _i_node("0");
  _i_def(state , "state", "0");

     switch(state)
     {   /* return the respective macro for the special character. */
         case 19:
         _i_node("1");
         _i_puse(state , "state");
         _i_loc("1", "2");
         _i_node("2");
          return(_i_cuse(LPAREN , "LPAREN", "2","global"));
         case 20:
         _i_node("1");
         _i_puse(state , "state");
         _i_loc("1", "3");
         _i_node("3");
          return(_i_cuse(RPAREN , "RPAREN", "3","global"));
         case 21:
         _i_node("1");
         _i_puse(state , "state");
         _i_loc("1", "4");
         _i_node("4");
          return(_i_cuse(LSQUARE , "LSQUARE", "4","global"));
         case 22:
         _i_node("1");
         _i_puse(state , "state");
         _i_loc("1", "5");
         _i_node("5");
          return(_i_cuse(RSQUARE , "RSQUARE", "5","global"));
         case 23:
         _i_node("1");
         _i_puse(state , "state");
         _i_loc("1", "6");
         _i_node("6");
          return(_i_cuse(QUOTE , "QUOTE", "6","global"));
         case 24:
         _i_node("1");
         _i_puse(state , "state");
         _i_loc("1", "7");
         _i_node("7");
          return(_i_cuse(BQUOTE , "BQUOTE", "7","global"));
         case 25:
         _i_node("1");
         _i_puse(state , "state");
         _i_loc("1", "8");
         _i_node("8");
          return(_i_cuse(COMMA , "COMMA", "8","global"));
         case 32:
         _i_node("1");
         _i_puse(state , "state");
         _i_loc("1", "9");
         _i_node("9");
          return(_i_cuse(EQUALGREATER , "EQUALGREATER", "9","global"));
         default:
         _i_node("1");
         _i_puse(state , "state");
         _i_loc("1", "10");
         _i_node("10");
          fprintf(stdout, "error\n");
          break;
     }
     _i_node("11");
     exit(0);
}

/* **********************************************************************
   Function name : skip
   Input         : character_stream
   Output        : void.
   Exceptions    : none.
   Description   : This function skips the comment part of the program.
                   It takes charcter_stream as input and reads character
                   until it finds new line character or
                   end_of_character_stream.
 * ******************************************************************* */

static skip(stream_ptr)
character_stream stream_ptr;
{
      _i_function("skip");
      _i_node("0");
      _i_def(stream_ptr , "stream_ptr", "0");
      _i_node("1");
        char c;
        _i_def(c , "c", "1");
        while(_i_node("2") && (_i_puse( _i_def( (c=get_char(_i_puse(stream_ptr , "stream_ptr")))!='\n' && !is_end_of_character_stream(_i_puse(stream_ptr , "stream_ptr")) , "c", "2"), "c"))){
          _i_loc("2", "3");
          _i_node("3");
        }
        _i_loc("2", "4");

             ; /* Skip the characters until EOF or EOL found. */
      	if(_i_node("4") && (_i_puse(c , "c")==EOF)){
          _i_loc("4", "5");
          _i_node("5");
          unget_char(_i_cuse(c , "c", "5"), _i_cuse(stream_ptr , "stream_ptr", "5")); /* Put back to leave gracefully - hf */
        }else{
          _i_loc("4", "6");
          _i_node("6");
        }
        _i_node("7");
        return;
}

/* *********************************************************************
   Function name : constant
   Input         : state of DFA, Token string, Token id.
   Output        : constant token.
   Exceptions    : none.
   Description   : This function returns the token_id for the constatnts
                   speccified by  the final state.
 * ****************************************************************** */

static int constant(state,token_str,token_ind)
int state,token_ind;
char token_str[];
{
  _i_function("constant");
  _i_node("0");
  _i_def(state , "state", "0");
  _i_def(token_str , "token_str", "0");
  _i_def(token_ind , "token_ind", "0");


     switch(state)
     {   /* Return the respective CONSTANT macro. */
         case 27 :
         _i_node("1");
         _i_puse(state , "state");
         _i_loc("1", "2");
         _i_node("2");
          return(_i_cuse(STRING_CONSTANT , "STRING_CONSTANT", "2","global"));
         case 29 :
         _i_node("1");
         _i_puse(state , "state");
         _i_loc("1", "3");
         _i_node("3");
         token_str[_i_cuse(token_ind , "token_ind", "3")-2]=' ';
         _i_def(token_str , "token_str", "3");
         _i_node("4");
         return(_i_cuse(CHARACTER_CONSTANT , "CHARACTER_CONSTANT", "4","global"));
         default :
         _i_node("1");
         _i_puse(state , "state");
         _i_loc("1", "5");
         _i_node("5");
         break;
     }
     _i_node("6");
}


/* *******************************************************************
   Function name : next_state
   Input         : current state, character
   Output        : next state of the DFA
   Exceptions    : none.
   Description   : This function returns the next state in the transition
                   diagram. The next state is determined by the current
                   state state and the inpu character ch.
 * ****************************************************************** */

static int next_state(state,ch)
int state;
char ch;
{
  _i_function("next_state");
  _i_node("0");
  _i_def(state , "state", "0");
  _i_def(ch , "ch", "0");

    if(_i_node("1") && (_i_puse(state , "state") < 0)){
      _i_loc("1", "2");
      _i_node("2");
      return(_i_cuse(state , "state", "2"));
    }else{
      _i_loc("1", "3");
      _i_node("3");
    }

    if(_i_node("4") && (_i_puse(base[_i_cuse(state , "state", "4")] , "base","global")+_i_puse(ch , "ch") >= 0))
    {
      _i_loc("4", "5");

        if(_i_node("5") &&(_i_puse( check[_i_cuse( base[_i_cuse(state , "state", "5")]+_i_cuse(ch , "ch", "5"), "base", "5","global")], "check","global") == _i_puse(state , "state"))){ /* Check for the right state */
            _i_loc("5", "6");
            _i_node("6");
             return(_i_cuse(next[_i_cuse(base[_i_cuse(state , "state", "6")] , "base", "6","global")+_i_cuse(ch , "ch", "6")] , "next", "6","global"));
        }
        else{
          _i_loc("5", "7");
          _i_node("7");
              return(next_state(_i_cuse(default1[_i_cuse(state , "state", "7")] , "default1", "7","global"),_i_cuse(ch , "ch", "7")));
        }
    }
    else{
      _i_loc("4", "8");
      _i_node("8");
      return(next_state(_i_cuse(default1[_i_cuse(state , "state", "8")] , "default1", "8","global"),_i_cuse(ch , "ch", "8")));
    }
    _i_node("9");
}

/* *********************************************************************
   Function name : is_eof_token
   Input         : token
   Output        : Boolean
   Exceptions    : none.
   Description   : This function checks whether the token t is eof_token
                   or not. If the integer value stored in the t is
                   EOTSTREAM then it is eof_token.
 * ***************************************************************** */

BOOLEAN is_eof_token(t)
token t;
{
  _i_function("is_eof_token");
  _i_node("0");
  _i_def(t , "t", "0");

    if(_i_node("1") && (_i_puse(t->token_id , "t")==_i_puse(EOTSTREAM , "EOTSTREAM","global"))){
      _i_loc("1", "2");
      _i_node("2");
        return(_i_cuse(TRUE , "TRUE", "2","global"));
    }else{
      _i_loc("1", "3");
      _i_node("3");
    }
    _i_node("4");
    return(_i_cuse(FALSE , "FALSE", "4","global"));
}

/* ********************************************************************
   Function name : print_token
   Input         : token
   Output        : Boolean
   Exceptions    : none.
   Description   : This function  prints the token. The token_id gives
                   the type of token not the token itself. So, in the
                   case of identifier,numeric,  string,character it is
                   required to print the actual token  from token_str.
                   So, precaution must be taken when printing the token.
                   This function is able to print the current token only
                   and it is the limitation of the program.
 * ******************************************************************** */

BOOLEAN print_token(token_ptr)
token token_ptr;
{
  _i_function("print_token");
  _i_node("0");
  _i_def(token_ptr , "token_ptr", "0");

     switch(token_ptr->token_id)
     {    /* Print the respective tokens. */
          case ERROR :
                      _i_node("1");
                      _i_puse(token_ptr , "token_ptr");
                      _i_puse(ERROR , "ERROR","global");
                      _i_loc("1", "2");
                      _i_node("2");

                      fprintf(stdout, "error,\t\"");
                      _i_node("3");
                      fprintf(stdout, "%s",_i_cuse(token_ptr->token_string , "token_ptr", "3"));
                      _i_node("4");
                      fprintf(stdout, "\".\n");
                      _i_node("5");
                      return(_i_cuse(TRUE , "TRUE", "5","global"));
          case EOTSTREAM :
                      _i_node("1");
                      _i_puse(token_ptr , "token_ptr");
                      _i_puse(EOTSTREAM , "EOTSTREAM","global");
                      _i_loc("1", "6");
                      _i_node("6");
                      fprintf(stdout, "eof.\n");
                      _i_node("7");
                      return(_i_cuse(TRUE , "TRUE", "7","global"));
          case 6 :
                      _i_node("1");
                      _i_puse(token_ptr , "token_ptr");
                      _i_loc("1", "8");
                      _i_node("8");
                      fprintf(stdout, "keyword,\t\"lambda\".\n");
                      _i_node("9");
                      return(_i_cuse(TRUE , "TRUE", "9","global"));
          case 9 :
                      _i_node("1");
                      _i_puse(token_ptr , "token_ptr");
                      _i_loc("1", "10");
                      _i_node("10");
                      fprintf(stdout, "keyword,\t\"and\".\n");
                      _i_node("11");
                      return(_i_cuse(TRUE , "TRUE", "11","global"));
          case 11:
                      _i_node("1");
                      _i_puse(token_ptr , "token_ptr");
                      _i_loc("1", "12");
                      _i_node("12");

                      fprintf(stdout, "keyword,\t\"or\".\n");
                      _i_node("13");
                      return(_i_cuse(TRUE , "TRUE", "13","global"));
          case 13:
                      _i_node("1");
                      _i_puse(token_ptr , "token_ptr");
                      _i_loc("1", "14");
                      _i_node("14");
                      fprintf(stdout, "keyword,\t\"if\".\n");
                      _i_node("15");
                      return(_i_cuse(TRUE , "TRUE", "15","global"));
          case 16:
                      _i_node("1");
                      _i_puse(token_ptr , "token_ptr");
                      _i_loc("1", "16");
                      _i_node("16");
                      fprintf(stdout, "keyword,\t\"xor\".\n");
                      _i_node("17");
                      return(_i_cuse(TRUE , "TRUE", "17","global"));
          case 17:
                      _i_node("1");
                      _i_puse(token_ptr , "token_ptr");
                      _i_loc("1", "18");
                      _i_node("18");
                      fprintf(stdout, "identifier,\t\"");
                      _i_node("19");
                      fprintf(stdout, "%s",_i_cuse(token_ptr->token_string , "token_ptr", "19"));
                      _i_node("20");
                      fprintf(stdout, "\".\n");
                      _i_node("21");
                      return(_i_cuse(TRUE , "TRUE", "21","global"));
          case 18:
                      _i_node("1");
                      _i_puse(token_ptr , "token_ptr");
                      _i_loc("1", "22");
                      _i_node("22");
                      fprintf(stdout, "numeric,\t");
                      _i_node("23");
                      fprintf(stdout, "%s",_i_cuse(token_ptr->token_string , "token_ptr", "23"));
                      _i_node("24");
                      fprintf(stdout, ".\n");
                      _i_node("25");
                      return(_i_cuse(TRUE , "TRUE", "25","global"));
          case 19:
                      _i_node("1");
                      _i_puse(token_ptr , "token_ptr");
                      _i_loc("1", "26");
                      _i_node("26");
                      fprintf(stdout, "lparen.\n");
                      _i_node("27");
                      return(_i_cuse(TRUE , "TRUE", "27","global"));
          case 20:
                      _i_node("1");
                      _i_puse(token_ptr , "token_ptr");
                      _i_loc("1", "28");
                      _i_node("28");
                      fprintf(stdout, "rparen.\n");
                      _i_node("29");
                      return(_i_cuse(TRUE , "TRUE", "29","global"));
          case 21:
                      _i_node("1");
                      _i_puse(token_ptr , "token_ptr");
                      _i_loc("1", "30");
                      _i_node("30");
                      fprintf(stdout, "lsquare.\n");
                      _i_node("31");
                      return(_i_cuse(TRUE , "TRUE", "31","global"));
          case 22:
                      _i_node("1");
                      _i_puse(token_ptr , "token_ptr");
                      _i_loc("1", "32");
                      _i_node("32");
                      fprintf(stdout, "rsquare.\n");
                      _i_node("33");
                      return(_i_cuse(TRUE , "TRUE", "33","global"));
          case 23:
                      _i_node("1");
                      _i_puse(token_ptr , "token_ptr");
                      _i_loc("1", "34");
                      _i_node("34");
                      fprintf(stdout, "quote.\n");
                      _i_node("35");
                      return(_i_cuse(TRUE , "TRUE", "35","global"));
          case 24:
                      _i_node("1");
                      _i_puse(token_ptr , "token_ptr");
                      _i_loc("1", "36");
                      _i_node("36");
                      fprintf(stdout, "bquote.\n");
                      _i_node("37");
                      return(_i_cuse(TRUE , "TRUE", "37","global"));
          case 25:
                      _i_node("1");
                      _i_puse(token_ptr , "token_ptr");
                      _i_loc("1", "38");
                      _i_node("38");
                      fprintf(stdout, "comma.\n");
                      _i_node("39");
                      return(_i_cuse(TRUE , "TRUE", "39","global"));
          case 27:
                      _i_node("1");
                      _i_puse(token_ptr , "token_ptr");
                      _i_loc("1", "40");
                      _i_node("40");
                      fprintf(stdout, "string,\t");
                      _i_node("41");
                      fprintf(stdout, "%s",_i_cuse(token_ptr->token_string , "token_ptr", "41"));
                      _i_node("42");
                      fprintf(stdout, ".\n");
                      _i_node("43");
                      return(_i_cuse(TRUE , "TRUE", "43","global"));
          case 29:
                      _i_node("1");
                      _i_puse(token_ptr , "token_ptr");
                      _i_loc("1", "44");
                      _i_node("44");
                      fprintf(stdout, "character,\t\"");
                      _i_node("45");
                      fprintf(stdout, "%s",_i_cuse(token_ptr->token_string , "token_ptr", "45"));
                      _i_node("46");
                      fprintf(stdout, "\".\n");
                      _i_node("47");
                      return(_i_cuse(TRUE , "TRUE", "47","global"));
          case 32:
                      _i_node("1");
                      _i_puse(token_ptr , "token_ptr");
                      _i_loc("1", "48");
                      _i_node("48");
                      fprintf(stdout, "keyword,\t\"=>\".\n");
                      _i_node("49");
                      return(_i_cuse(TRUE , "TRUE", "49","global"));
          default:
                      _i_node("1");
                      _i_puse(token_ptr , "token_ptr");
                      _i_loc("1", "50");
                      _i_node("50");
                      break;
      }
      _i_node("51");
      return(_i_cuse(FALSE , "FALSE", "51","global"));
}

/* **********************************************************************
   Function name : get_actual_token
   Input         : token string and token id.
   Output        : void.
   Exceptions    : none.
   Description   : This function prints the actual token in the case of
                   identifier,numeric,string and character. It removes
                   the leading and trailing  spaces and prints the token.
 * ****************************************************************** */

static get_actual_token(token_str,token_ind)
int token_ind;
char token_str[];
{
    _i_function("get_actual_token");
    _i_node("0");
    _i_def(token_str , "token_str", "0");
    _i_def(token_ind , "token_ind", "0");

    _i_node("1");
          int ind,start;
    _i_def(ind, "ind", "1");
    _i_def(start , "start", "1");
          for(_i_node("2"),ind=_i_cuse(token_ind , "token_ind", "2"),_i_def(ind , "ind", "2");_i_node("3") && (_i_puse(ind , "ind")>0 && isspace(_i_puse(token_str[_i_cuse(ind , "ind", "3")-1], "token_str")));_i_node("5"), _i_cuse(_i_def(_i_cuse(--ind, "ind", "5"), "ind", "5") , "ind", "5")){
            _i_loc("3", "4");
            _i_node("4");
          }
          _i_loc("3", "6");
          _i_node("6");
                        /* Delete the trailing white spaces & protect - hf */
           token_str[_i_cuse(ind , "ind", "6")]='\0';
           _i_def(token_str , "token_str", "6");
           _i_node("7");
           token_ind=_i_cuse(ind , "ind", "7");
           _i_def(token_ind , "token_ind", "7");

          for(_i_node("8"),ind=0,_i_def(ind , "ind", "8");_i_node("9") && (_i_puse(ind , "ind")<_i_puse(token_ind , "token_ind"));_i_node("13"), _i_cuse(_i_def(_i_cuse(++ind, "ind", "13"), "ind", "13") , "ind", "13")){
              _i_loc("9", "10");

                if(_i_node("10") && (!isspace(_i_puse( token_str[_i_cuse(ind , "ind", "10")], "token_str")))){
                  _i_loc("10", "11");
                  _i_node("11");
                      break;
                }else{
                  _i_loc("10", "12");
                  _i_node("12");
                }
          }
          _i_loc("9", "14");
          for(_i_node("14"),start=0,_i_def(start , "start", "14");_i_node("15") && (_i_puse(ind , "ind")<=_i_puse(token_ind , "token_ind"));_i_node("17"), _i_cuse(_i_def(_i_cuse(++start, "start", "17"), "start", "17") , "start", "17"),  _i_cuse(_i_def(_i_cuse(++ind, "ind", "17"), "ind", "17") , "ind", "17"))
          {
            /* Delete the leading
                                                       white spaces. */
            _i_loc("15", "16");
            _i_node("16");
                token_str[_i_cuse(start , "start", "16")]=_i_cuse(token_str[_i_cuse(ind , "ind", "16")] , "token_str", "16");
                _i_def(token_str , "token_str", "16");
          }
          _i_loc("15", "18");
          _i_node("18");
          return;
}
