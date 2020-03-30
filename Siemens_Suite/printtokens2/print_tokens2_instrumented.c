/***********************************************/
/*  assgnment.5  Shu Z. A00042813 for CS453    */
/*  using the tokenizer and stream module      */
/*  print_tokens.c Code                        */
/***********************************************/

/***********************************************/
/* NAME:	print_tokens                   */
/* INPUT:	a filename                     */
/* OUTPUT:      print out the token stream     */
/* DESCRIPTION: using the tokenizer interface  */
/*              to print out the token stream  */
/***********************************************/
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "tokens.h"
#define TRUE 1
#define FALSE 0

/* instrumentation */
 #define _i_function(VAR)     char _v_par1[50], _v_par2[50], _v_par3[50], _v_temp[50], _v_scope[50], _v_function[50] = VAR
 #define _i_node(NODE)        (printf( "node %s.%s\n", _v_function, NODE),NODE)
 #define _i_def(DATA,...)     (sprintf(_v_temp,"%s %s %s",__VA_ARGS__,__VA_ARGS__,__VA_ARGS__),sscanf(_v_temp,"%s %s %s", _v_par1, _v_par2, _v_par3),printf( "def %s.%s %s.%s\n", (strcmp(_v_par1,_v_par3)?_v_par3:_v_function), _v_par1, _v_function, _v_par2),DATA)
 #define _i_cuse(DATA,...)    (sprintf(_v_temp,"%s %s %s",__VA_ARGS__,__VA_ARGS__,__VA_ARGS__),sscanf(_v_temp,"%s %s %s", _v_par1, _v_par2, _v_par3),printf( "c_use %s.%s %s.%s\n", (strcmp(_v_par1,_v_par3)?_v_par3:_v_function), _v_par1, _v_function, _v_par2), DATA)
 #define _i_puse(DATA,...)    (sprintf(_v_temp,"%s %s %s",__VA_ARGS__,__VA_ARGS__,__VA_ARGS__),sscanf(_v_temp,"%s %s %s", _v_par1, _v_par2, _v_par3),printf( "p_use %s.%s %s\n", (strcmp(_v_par1,_v_par2)?_v_par2:_v_function), _v_par1, _v_function), DATA)
 #define _i_loc(NODE1,NODE2)  (printf( "loc %s.%s-%s.%s %s\n", _v_function, NODE1, _v_function, NODE2, _v_function))
 #define _i_scope(LINE)       (sprintf(_v_scope,"%s_%s",_v_function,LINE),_v_scope)

/*#define _i_function(VAR)     char _v_par1[50], _v_par2[50], _v_par3[50], _v_temp[50], _v_scope[50], _v_function[50] = VAR
#define _i_node(NODE)        (NODE)
#define _i_def(DATA,...)     (sprintf(_v_temp,"%s %s %s",__VA_ARGS__,__VA_ARGS__,__VA_ARGS__),sscanf(_v_temp,"%s %s %s", _v_par1, _v_par2, _v_par3),DATA)
#define _i_cuse(DATA,...)    (sprintf(_v_temp,"%s %s %s",__VA_ARGS__,__VA_ARGS__,__VA_ARGS__),sscanf(_v_temp,"%s %s %s", _v_par1, _v_par2, _v_par3), DATA)
#define _i_puse(DATA,...)    (sprintf(_v_temp,"%s %s %s",__VA_ARGS__,__VA_ARGS__,__VA_ARGS__),sscanf(_v_temp,"%s %s %s", _v_par1, _v_par2, _v_par3), DATA)
#define _i_loc(NODE1,NODE2)  (NODE1)
#define _i_scope(LINE)       (sprintf(_v_scope,"%s_%s",_v_function,LINE),_v_scope)*/
/* --------------- */
char buffer[81];  /* fixed array length MONI */ /* to store the token temporar */

void global_sets(){
  _i_function("global");
  _i_node("0");
  _i_def(TRUE , "TRUE", "0");
  _i_def(FALSE , "FALSE", "0");
  _i_def(buffer , "buffer", "0");
}

main(argc,argv)
int argc;
char *argv[3];
{
  global_sets();
  _i_function("main");
  _i_node("0");
  _i_def(argc , "argc", "0");
  _i_def(argv , "argv", "0");

  _i_node("1");
   char *fname;
   token tok;
   token_stream tp;
   _i_def(fname , "fname", "1");
   _i_def(tok , "tok", "1");
   _i_def(tp , "tp", "1");

     if(_i_node("2") && _i_puse(argc , "argc")==1)                  /* if not given filename,take as '""' */
       {
         _i_loc("2", "3");
         _i_node("3");
        fname= (char *) malloc(sizeof(char));
        _i_def(fname , "fname", "3");
        _i_node("4");
        *fname = '\0';
        _i_def(fname , "fname", "4");

       }
     else{
       _i_loc("2", "5");


      if(_i_node("5") && _i_puse(argc , "argc")==2){
        _i_loc("5", "6");
        _i_node("6");
        fname= _i_cuse(argv[1] , "argv", "6");
        _i_def(fname , "fname", "6");
      }
       else
       {
         _i_loc("5", "7");
         _i_node("7");
          fprintf(stdout, "Error!,please give the token stream\n");
         exit(0);
       }
     }
     _i_node("8");
    tp=open_token_stream(_i_cuse(fname, "fname", "8"));  /* open token stream */
    _i_def(tp , "tp", "8");
    _i_node("9");
    tok=get_token(_i_cuse(tp , "tp", "9"));
    _i_def(tok , "tok", "9");

    while (_i_node("9") && (is_eof_token(_i_puse(tok , "tok")) ==_i_puse(FALSE , "FALSE","global"))) /* take one token each time until eof */
    {
      _i_loc("9", "10");
      _i_node("10");
       print_token(_i_cuse(tok , "tok", "10"));
       _i_node("11");
       tok=get_token(_i_cuse(tp , "tp", "11"));
       _i_def(tok , "tok", "11");
    }
    _i_loc("9", "11");
    _i_node("11");
    print_token(_i_cuse(tok , "tok", "11")); /* print eof signal */
    exit(0);
}

/* stream.c code */

/***********************************************/
/* NMAE:	open_character_stream          */
/* INPUT:       a filename                     */
/* OUTPUT:      a pointer to chacracter_stream */
/* DESCRIPTION: when not given a filename,     */
/*              open stdin,otherwise open      */
/*              the existed file               */
/***********************************************/
character_stream open_character_stream(fname)
char *fname;
{
  _i_function("open_character_stream");
  _i_node("0");
  _i_def(fname , "fname", "0");

  _i_node("1");
  character_stream fp;
  _i_def(fp , "fp", "1");

  if(_i_node("2") && (_i_puse(fname , "fname") == NULL)){
    _i_loc("2", "3");
    _i_node("3");
     fp=_i_cuse(stdin , "stdin", "3");
     _i_def(fp , "fp", "3");
   }
  else{
    _i_loc("2", "4");
        if (_i_node("4") && ((_i_puse(_i_def(fp=fopen(_i_cuse(fname , "fname", "4"),"r"), "fp", "4"), "fp")== NULL))){
          _i_loc("4", "5");
          _i_node("5");
         fprintf(stdout, "The file %s doesn't exists\n",_i_cuse(fname , "fname", "5"));
         exit(0);
       }
       else{
         _i_loc("4", "6");
         _i_node("6");

       }
   }
   _i_node("7");
  return(_i_cuse(fp , "fp", "7"));
}

/**********************************************/
/* NAME:	get_char                      */
/* INPUT:       a pointer to char_stream      */
/* OUTPUT:      a character                   */
/**********************************************/
char get_char(fp)
character_stream fp;
{
  _i_function("get_char");
  _i_node("0");
  _i_def(fp , "fp", "0");

  _i_node("1");
  char ch;
  _i_def(ch , "ch", "1");
  _i_node("2");
  ch=getc(_i_cuse(fp , "fp", "2"));
  _i_def(ch , "ch", "2");
  _i_node("3");
  return(_i_cuse(ch , "ch", "3"));
}

/***************************************************/
/* NAME:      unget_char                           */
/* INPUT:     a pointer to char_stream,a character */
/* OUTPUT:    a character                          */
/* DESCRIPTION:when unable to put back,return EOF  */
/***************************************************/
char unget_char(ch,fp)
character_stream fp;
char ch;
{
  _i_function("unget_char");
  _i_node("0");
  _i_def(ch , "ch", "0");
  _i_def(fp , "fp", "0");

  _i_node("1");
  char c;
  _i_def(c , "c", "1");

  _i_node("2");
  c=ungetc(_i_cuse(ch , "ch", "2"),_i_cuse(fp , "fp", "2"));
  _i_def(c , "c", "2");
  if(_i_node("3")&& (_i_puse(c , "c") ==EOF))
    {
    _i_loc("3", "4");
    _i_node("4");
     return(_i_cuse(c , "c", "4"));
    }
  else{
    _i_loc("3", "5");
    _i_node("5");
     return(_i_cuse(c , "c", "5"));
   }
}

/* tokenizer.c code */


// char buffer[81];  /* fixed array length MONI */ /* to store the token temporar */


static int is_spec_symbol();
static int is_token_end();
static unget_error();
static int is_keyword();
static int is_identifier();
static int is_num_constant();
static int is_char_constant();
static int is_str_constant();
static int is_comment();
static void print_spec_symbol();

/********************************************************/
/* NAME:	open_token_stream                       */
/* INPUT:       a filename                              */
/* OUTPUT:      a pointer to a token_stream             */
/* DESCRIPTION: when filename is EMPTY,choice standard  */
/*              input device as input source            */
/********************************************************/
token_stream open_token_stream(fname)
char *fname;
{
  _i_function("open_token_stream");
  _i_node("0");
  _i_def(fname , "fname", "0");
  _i_node("1");
  token_stream fp;
  _i_def(fp , "fp", "1");
 if(_i_node("2") && (strcmp(_i_puse(fname , "fname"),"")==0)){
   _i_loc("2", "3");
   _i_node("3");
      fp=open_character_stream(NULL);
      _i_def(fp , "fp", "3");
 }
 else{
   _i_loc("2", "4");
   _i_node("4");
      fp=open_character_stream(_i_cuse(fname , "fname", "4"));
      _i_def(fp , "fp", "4");
  }
  _i_node("5");
 return(_i_cuse(fp , "fp", "5"));
}

/********************************************************/
/* NAME :	get_token                               */
/* INPUT: 	a pointer to the tokens_stream          */
/* OUTPUT:      a token                                 */
/* DESCRIPTION: according the syntax of tokens,dealing  */
/*              with different case  and get one token  */
/********************************************************/
token get_token(tp)
token_stream tp;
{
  _i_function("get_token");
  _i_node("0");
  _i_def(tp , "tp", "0");
  _i_node("1");
  int i=0,j;
  int id=0;
  char ch,ch1[2];
_i_def(i , "i", "1");
_i_def(j , "j", "1");
_i_def(id , "id", "1");
_i_def(ch , "ch", "1");
_i_def(ch1 , "ch1", "1");

  for (_i_node("2"),j=0,_i_def(j , "j", "2");_i_node("3") && (_i_puse(j , "j")<=80);_i_node("5"),_i_def(_i_cuse(j++ , "j", "5") , "j", "5"))          /* initial the buffer   */
      {
        _i_loc("3", "4");
        _i_node("4");
        buffer[_i_cuse(j , "j", "4")]='\0';
        _i_def(buffer , "buffer", "4");
      }
      _i_loc("3", "6");
      _i_node("6");
   ch1[0]='\0';
   _i_def(ch1 , "ch1", "6");
   _i_node("7");
   ch1[1]='\0';
   _i_def(ch1 , "ch1", "7");
   _i_node("8");
   ch=get_char(_i_cuse(tp , "tp", "8"));
   _i_def(ch , "ch", "8");
   while(_i_node("9") && (_i_puse(ch , "ch")==' '||_i_puse(ch , "ch")=='\n'))      /* strip all blanks until meet characters */
      {
        _i_loc("9", "10");
        _i_node("10");
       ch=get_char(_i_cuse(tp , "tp", "10"));
       _i_def(ch , "ch", "10");
      }
      _i_loc("9", "11");
      _i_node("11");
    buffer[_i_cuse(i , "i", "11")]=_i_cuse(ch , "ch", "11");
   _i_def(buffer , "buffer", "11");

   if(_i_node("12") && (is_eof_token(_i_puse(buffer , "buffer"))==_i_puse(TRUE , "TRUE","global"))){
     _i_loc("12", "13");
     _i_node("13");
     return(_i_cuse(buffer , "buffer", "13"));
   }else{
     _i_loc("12", "14");
     _i_node("14");
   }
   if(_i_node("15") && (is_spec_symbol(_i_puse(buffer , "buffer"))==_i_puse(TRUE , "TRUE","global"))){
     _i_loc("15", "16");
     _i_node("16");
     return(_i_cuse(buffer , "buffer", "16"));
   }else{
    _i_loc("15", "17");
    _i_node("17");
   }

   if(_i_node("18") && (_i_puse(ch , "ch") =='"')){
     _i_loc("18", "19");
     _i_node("19");
     id=1;    /* prepare for string */
     _i_def(id , "id", "19");
   }else{
     _i_loc("18", "20");
     _i_node("20");
   }

   if(_i_node("21") && (_i_puse(ch , "ch") ==59)){
     _i_loc("21", "22");
     _i_node("22");
     id=2;    /* prepare for comment */
     _i_def(id , "id", "22");
   }else{
     _i_loc("21", "23");
     _i_node("23");
   }
   _i_node("24");
   ch=get_char(_i_cuse(tp , "tp", "24"));
   _i_def(ch , "ch", "24");
   while (_i_node("25") && (is_token_end(_i_cuse(id , "id", "25"),_i_cuse(ch , "ch", "25")) == _i_puse(FALSE , "FALSE","global")))/* until meet the end character */
   {
     _i_loc("25", "26");
     _i_node("26");
     _i_def(_i_cuse(i++ , "i", "26") , "i", "26");
     _i_node("27");
       buffer[_i_cuse(i , "i", "27")]=_i_cuse(ch , "ch", "27");
       _i_def(buffer , "buffer", "27");
       _i_node("28");
       ch=get_char(_i_cuse(tp , "tp", "28"));
       _i_def(ch , "ch", "28");
   }
   _i_loc("25", "29");
   _i_node("29");
   ch1[0]=_i_cuse(ch , "ch", "29");                        /* hold the end charcater          */
   _i_def(ch1 , "ch1", "29");

   if(_i_node("30") && (is_eof_token(_i_cuse(ch1 , "ch1", "30"))==_i_puse(TRUE , "TRUE","global")))       /* if end character is eof token    */
      {
        _i_loc("30", "31");
        _i_node("31");
         ch=unget_char(_i_cuse(ch , "ch", "31"),_i_cuse(tp , "tp", "31"));        /* then put back eof on token_stream */
         _i_def(ch , "ch", "31");

        if(_i_node("32") && (_i_puse(ch , "ch")==EOF)){
          _i_loc("32", "33");
          _i_node("33");
          unget_error(_i_cuse(tp , "tp", "33"));
        }else{
          _i_loc("32", "34");
          _i_node("34");
        }
        _i_node("35A");
        return(_i_cuse(buffer , "buffer", "35A"));
      }else{
        _i_loc("30", "30A");
        _i_node("30A");

      }

   if(_i_node("35") && (is_spec_symbol(_i_cuse(ch1 , "ch1", "35"))==_i_puse(TRUE , "TRUE","global")))     /* if end character is special_symbol */
      {
        _i_loc("35", "36");
        _i_node("36");
        ch=unget_char(_i_cuse(ch , "ch", "36"),_i_cuse(tp , "tp", "36"));        /* then put back this character       */
        _i_def(ch , "ch", "36");
        if(_i_node("37") && (_i_puse(ch , "ch")==EOF)){
          _i_loc("37", "38");
          _i_node("38");
          unget_error(_i_cuse(tp , "tp", "38"));
        }else{
          _i_loc("38", "39");
          _i_node("40");
        }
        _i_node("41");
        return(_i_cuse(buffer , "buffer", "41"));
      }else{
        _i_loc("35", "42");
        _i_node("42");
      }

   if(_i_node("43") && (_i_puse(id , "id")==1))                  /* if end character is " and is string */
     {
       _i_loc("43", "44");
       _i_node("44");
       _i_def(_i_cuse(i++ , "i", "44") , "i", "44");                     /* case,hold the second " in buffer    */
       _i_node("45");
       buffer[_i_cuse(i , "i", "45")]=_i_cuse(ch , "ch", "45");
       _i_def(buffer , "buffer", "45");
       _i_node("46");
       return(_i_cuse(buffer , "buffer", "46"));
     }else{
       _i_loc("43", "47");
       _i_node("47");

     }

   if(_i_node("48") && (_i_puse(id , "id")==0 && _i_puse(ch , "ch")==59))
                                   /* when not in string or comment,meet ";" */
     {
       _i_loc("48", "49");
       _i_node("49");
         ch=unget_char(_i_cuse(ch , "ch", "49"),_i_cuse(tp , "tp", "49"));       /* then put back this character         */
         _i_def(ch , "ch", "49");
         if(_i_node("50")&&(_i_puse(ch , "ch")==EOF)){
           _i_loc("50", "51");
           _i_node("51");
           unget_error(_i_cuse(tp , "tp", "51"));
         }else{
           _i_loc("50", "52");
           _i_node("52");

         }
         _i_node("53");
       return(_i_cuse(buffer , "buffer", "53"));
     }else{
       _i_loc("48", "54");
       _i_node("54");
     }
     _i_node("55");
  return(_i_cuse(buffer , "buffer", "55"));                   /* return nomal case token             */
}

/*******************************************************/
/* NAME:	is_token_end                           */
/* INPUT:       a character,a token status             */
/* OUTPUT:	a BOOLEAN value                        */
/*******************************************************/
static int is_token_end(str_com_id,ch)
char ch;
int str_com_id;
{
_i_function("is_token_end");
_i_node("0");
_i_def(ch , "ch", "0");
_i_def(str_com_id , "str_com_id", "0");

_i_node("1");

  char ch1[2];  /* fixed array declaration MONI */
_i_def(ch1 , "ch1", "1");
_i_node("2");
 ch1[0]=_i_cuse(ch , "ch", "2");
 _i_def(ch1 , "ch1", "2");
 _i_node("3");
 ch1[1]='\0';
 _i_def(ch1 , "ch1", "3");

 if(_i_node("4") && (is_eof_token(_i_cuse(ch1 , "ch1", "4"))==_i_puse(TRUE , "TRUE","global"))){
   _i_loc("4", "5");
   _i_node("5");
   return(_i_cuse(TRUE , "TRUE", "5","global")); /* is eof token? */
 }else{
   _i_loc("4", "6");
   _i_node("6");
 }

 if(_i_node("7") && (_i_puse(str_com_id , "str_com_id")==1))          /* is string token */
    {
      _i_loc("7", "8");
       if(_i_node("8") && (_i_puse(ch , "ch")=='"' | _i_puse(ch , "ch")=='\n')){   /* for string until meet another " */
        _i_loc("8", "9");
        _i_node("9");
         return(_i_cuse(TRUE , "TRUE", "9","global"));
       }
      else{
        _i_loc("8", "10");
        _i_node("10");
         return(_i_cuse(FALSE , "FALSE", "10","global"));
       }
    }else{
      _i_loc("7", "11");
      _i_node("11");
    }

 if(_i_node("12") && (_i_puse(str_com_id , "str_com_id")==2))    /* is comment token */
   {
     _i_loc("12", "13");

     if(_i_node("13") && (_i_puse(ch , "ch")=='\n')){     /* for comment until meet end of line */
       _i_loc("13", "14");
       _i_node("14");
        return(_i_cuse(TRUE , "TRUE", "14","global"));
      }
      else{
        _i_loc("13", "15");
        _i_node("15");
        return(_i_cuse(FALSE , "FALSE", "15","global"));
      }
   }else{
     _i_loc("12", "16");
     _i_node("16");

   }

 if(_i_node("17") && (is_spec_symbol(_i_cuse(ch1 , "ch1", "17"))==_i_puse(TRUE , "TRUE","global"))){
   _i_loc("17", "18");
   _i_node("18");
    return(_i_cuse(TRUE , "TRUE", "18","global")); /* is special_symbol? */
 }else{
   _i_loc("17", "19");
   _i_node("19");
 }

 if(_i_node("20") && (_i_puse(ch , "ch") ==' ' || _i_puse(ch , "ch")=='\n' || _i_puse(ch , "ch")==59)){
   _i_loc("20", "21");
   _i_node("21");
   return(_i_cuse(TRUE , "TRUE", "21","global"));
 }else{
   _i_loc("20", "22");
   _i_node("22");
 }
 _i_node("23");
                              /* others until meet blank or tab or 59 */
 return(_i_cuse(FALSE , "FALSE", "23","global"));               /* other case,return FALSE */
}

/****************************************************/
/* NAME :	token_type                          */
/* INPUT:       a pointer to the token              */
/* OUTPUT:      an integer value                    */
/* DESCRIPTION: the integer value is corresponding  */
/*              to the different token type         */
/****************************************************/
static int token_type(tok)
token tok;
{
  _i_function("token_type");
  _i_node("0");
  _i_def(tok , "tok", "0");

 if(_i_node("1") && (is_keyword(_i_puse(tok , "tok")))){
   _i_loc("1", "2");
   _i_node("2");
   return(_i_cuse(keyword , "keyword", "2"));
 }else{
   _i_loc("1", "3");
   _i_node("3");
 }
 if(_i_node("4") && (is_spec_symbol(_i_puse(tok , "tok")))){
   _i_loc("4", "5");
   _i_node("5");
   return(_i_cuse(spec_symbol , "spec_symbol", "5"));
 }else{
   _i_loc("4", "6");
   _i_node("6");
 }
 if(_i_node("7") && (is_identifier(_i_puse(tok , "tok")))){
   _i_loc("7", "8");
   _i_node("8");
   return(_i_cuse(identifier , "identifier", "8"));
 }else{
   _i_loc("8", "9");
   _i_node("9");
 }
 if(_i_node("10") && (is_num_constant(_i_puse(tok , "tok")))){
   _i_loc("10", "11");
   _i_node("11");
   return(_i_cuse(num_constant , "num_constant", "11"));
 }else{
   _i_loc("10", "12");
   _i_node("12");
 }
 if(_i_node("13") && (is_str_constant(_i_puse(tok , "tok")))){
   _i_loc("13", "14");
   _i_node("14");
   return(_i_cuse(str_constant , "str_constant", "14"));
 }else{
   _i_loc("13", "15");
   _i_node("15");
 }
 if(_i_node("16") && (is_char_constant(_i_puse(tok , "tok")))){
   _i_loc("16", "17");
   _i_node("17");
   return(_i_cuse(char_constant , "char_constant", "17"));
 }else{
   _i_loc("16", "18");
   _i_node("18");
 }

 if(_i_node("19") && (is_comment(_i_puse(tok , "tok")))){
   _i_loc("19", "20");
   _i_node("20");
   return(_i_cuse(comment , "comment", "20"));
 }else{
   _i_loc("19", "21");
   _i_node("21");
 }
 if(_i_node("22") && (is_eof_token(_i_puse(tok , "tok")))){
   _i_loc("22", "23");
   _i_node("23");
   return(_i_cuse(end , "end", "23"));
 }else{
   _i_loc("22", "24");
   _i_node("24");

 }
 _i_node("25");
 return(_i_cuse(error , "error", "25"));                    /* else look as error token */
}

/****************************************************/
/* NAME:	print_token                         */
/* INPUT:	a pointer to the token              */
/* OUTPUT:      a BOOLEAN value,print out the token */
/*              according the forms required        */
/****************************************************/
int print_token(tok)
token tok;
{
  _i_function("print_token");
  _i_node("0");
  _i_def(tok , "tok", "0");

  _i_node("1");
  int type;
  _i_def(type , "type", "1");
  _i_node("2");
  type=token_type(_i_cuse(tok , "tok", "2"));
  _i_def(type , "type", "2");
 if(_i_node("3") && (_i_puse(type , "type")==_i_puse(error , "error")))
   {
     _i_loc("3", "4");
     _i_node("4");
      fprintf(stdout, "error,\"%s\".\n",_i_cuse(tok , "tok", "4"));
   }else{
     _i_loc("3", "5");
     _i_node("5");
   }
 if(_i_node("6") && (_i_puse(type , "type")==_i_puse(keyword , "keyword")))
   {
     _i_loc("6", "7");
     _i_node("7");
     fprintf(stdout, "keyword,\"%s\".\n",_i_cuse(tok , "tok", "7"));
   }else{
     _i_loc("6", "8");
     _i_node("8");
   }

 if(_i_node("9") && (_i_puse(type , "type")==_i_puse(spec_symbol , "spec_symbol"))){
   _i_loc("9", "10");
   _i_node("10");
   print_spec_symbol(_i_cuse(tok , "tok", "10"));
 }else{
   _i_loc("9", "11");
   _i_node("11");

 }

 if(_i_node("12") && (_i_puse(type , "type")==_i_puse(identifier , "identifier")))
   {
     _i_loc("12", "13");
     _i_node("13");
     fprintf(stdout, "identifier,\"%s\".\n",_i_cuse(tok , "tok", "13"));
   }else{
     _i_loc("12", "14");
     _i_node("14");
   }

 if(_i_node("15") && (_i_puse(type , "type")==_i_puse(num_constant , "num_constant")))
   {
     _i_loc("15", "16");
     _i_node("16");
     fprintf(stdout, "numeric,%s.\n",_i_cuse(tok , "tok", "16"));
   }else{
     _i_loc("15", "17");
     _i_node("17");
   }

 if(_i_node("18") && (_i_puse(type , "type")==_i_puse(str_constant , "str_constant")))
   {
     _i_loc("18", "19");
     _i_node("19");
     fprintf(stdout, "string,%s.\n",_i_cuse(tok , "tok", "19"));
   }else{
     _i_loc("18", "20");
     _i_node("20");
   }

 if(_i_node("21") && (_i_puse(type , "type")==_i_puse(char_constant , "char_constant")))
   {
     _i_loc("21", "22");
     _i_node("22");
    tok=_i_cuse(tok , "tok", "22")+1;
    _i_def(tok , "tok", "22");
    _i_node("23");
    fprintf(stdout, "character,\"%s\".\n",_i_cuse(tok , "tok", "23"));
  }else{
    _i_loc("21", "23");
    _i_node("23");
  }

   if(_i_node("24") && (_i_puse(type , "type")==_i_puse(end , "end"))){
     _i_loc("24", "25");
     _i_node("25");
     fprintf(stdout, "eof.\n");
   }else{
     _i_loc("24", "26");
     _i_node("26");
   }
  }

/* the code for tokens judgment function */

/*************************************/
/* NAME:	is_eof_token         */
/* INPUT: 	a pointer to a token */
/* OUTPUT:      a BOOLEAN value      */
/*************************************/
int is_eof_token(tok)
token tok;
{
  _i_function("is_eof_token");
  _i_node("0");
  _i_def(tok , "tok", "0");

  if(_i_node("1")&& (_i_cuse(*tok , "tok", "1")==EOF)){
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

/*************************************/
/* NAME:	is_comment           */
/* INPUT: 	a pointer to a token */
/* OUTPUT:      a BOOLEAN value      */
/*************************************/
static int is_comment(ident)
token ident;
{
  _i_function("is_comment");
  _i_node("0");
  _i_def(ident , "ident", "0");

  if(_i_node("1")&& (_i_puse((*ident) , "ident") ==59) ){   /* the char is 59   */
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

/*************************************/
/* NAME:	is_keyword           */
/* INPUT: 	a pointer to a token */
/* OUTPUT:      a BOOLEAN value      */
/*************************************/
static int is_keyword(str)
    token  str;
{
  _i_function("is_keyword");
  _i_node("0");
  _i_def(str , "str", "0");

 if (_i_node("1") && (!strcmp(_i_puse(str , "str"),"and") || !strcmp(_i_puse(str , "str"),"or") || !strcmp(_i_puse(str , "str"),"if") ||
    !strcmp(_i_puse(str , "str"),"xor")||!strcmp(_i_puse(str , "str"),"lambda")||!strcmp(_i_puse(str , "str"),"=>"))){
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

/*************************************/
/* NAME:	is_char_constant     */
/* INPUT: 	a pointer to a token */
/* OUTPUT:      a BOOLEAN value      */
/*************************************/
static int is_char_constant(str)
    token str;
{
  _i_function("is_char_constant");
  _i_node("0");
  _i_def(str , "str", "0");

  if (_i_node("1") && ((_i_puse(*str , "str"))=='#' && isalpha(*(_i_puse(str , "str")+1)))){
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

/*************************************/
/* NAME:	is_num_constant      */
/* INPUT: 	a pointer to a token */
/* OUTPUT:      a BOOLEAN value      */
/*************************************/
static int is_num_constant(str)
    token  str;
{
  _i_function("is_num_constant");
  _i_node("0");
  _i_def(str , "str", "0");
  _i_node("1");
  int i=1;
  _i_def(i , "i", "1");
  if (_i_node("2") && (isdigit(_i_puse(*str , "str"))))
    {
      _i_loc("2", "3");
    while (_i_node("3") && (*(_i_puse(str , "str")+_i_puse(i , "i")) != '\0') )   /* until meet token end sign */
      {
        _i_loc("3", "4");
       if(_i_node("4") && (isdigit(*(_i_puse(str , "str")+_i_puse(i , "i"))))){
         _i_loc("4", "5");
         _i_def(_i_cuse(i++ , "i", "5") , "i", "5");
       }
       else{
         _i_loc("4", "6");
         _i_node("6");
         return(_i_cuse(FALSE , "FALSE", "6","global"));
       }
      }                         /* end WHILE */
      _i_loc("3", "7");
      _i_node("7");

    return(_i_cuse(TRUE , "TRUE", "7","global"));
    }
  else{
    _i_loc("2", "8");
    _i_node("8");
   return(_i_cuse(FALSE , "FALSE", "8","global"));               /* other return FALSE */
 }
}

/*************************************/
/* NAME:	is_str_constant      */
/* INPUT: 	a pointer to a token */
/* OUTPUT:      a BOOLEAN value      */
/*************************************/
static int is_str_constant(str)
    token str;
{
  _i_function("is_str_constant");
  _i_node("0");
  _i_def(str , "str", "0");
  _i_node("1");
  int i=1;
  _i_def(i , "i", "1");

  if (_i_node("2") && (_i_puse(*str , "str") =='"'))
     {
       _i_loc("2", "3");
       while (_i_node("3") && (*(_i_puse(str , "str")+_i_puse(i , "i"))!='\0'))  /* until meet the token end sign */
         {
           _i_loc("3", "4");

            if(_i_node("4") && (*(_i_puse(str , "str")+_i_puse(i , "i"))=='"')){
              _i_loc("4", "5");
              _i_node("5");
              return(_i_cuse(TRUE , "TRUE", "5","global"));        /* meet the second '"'           */
            }
           else{
             _i_loc("4", "6");
             _i_node("6");
             _i_def(_i_cuse(i++ , "i", "6") , "i", "6");
           }
         }               /* end WHILE */
         _i_loc("3", "7");
         _i_node("7");
     return(_i_cuse(FALSE , "FALSE", "7","global"));
    }
  else{
    _i_loc("2", "8");
    _i_node("8");
    return(_i_cuse(FALSE , "FALSE", "8","global"));       /* other return FALSE */
  }
}
/*************************************/
/* NAME:	is_identifier         */
/* INPUT: 	a pointer to a token */
/* OUTPUT:      a BOOLEAN value      */
/*************************************/
static int is_identifier(str)
    token  str;
{
_i_function("is_identifier");
_i_node("0");
  _i_def(str , "str", "0");

_i_node("1");
  int i=1;
  _i_def(i , "i", "1");



  if (_i_node("2") && (isalpha( _i_puse(*str , "str"))) )
     {
       _i_loc("2", "3");
        while(_i_node("3") &&  (*(_i_puse(str , "str")+_i_puse(i , "i")) !='\0') )   /* unti meet the end token sign */
           {
             _i_loc("3", "4");
            if(_i_node("4") && (isalpha(*(_i_puse(str , "str")+_i_puse(i , "i"))) || isdigit(*(_i_puse(str , "str")+_i_puse(i , "i"))))){
              _i_loc("4", "5");
              _i_node("5");
              _i_def(_i_cuse(i++ , "i", "5") , "i", "5");
             }
            else{
              _i_loc("4", "6");
              _i_node("6");
               return(_i_cuse(FALSE , "FALSE", "6","global"));
             }
           }      /* end WHILE */
           _i_loc("3", "7");
           _i_node("7");

     return(_i_cuse(TRUE , "TRUE", "7","global"));
     }
  else{
    _i_loc("2", "8");
    _i_node("8");
     return(_i_cuse(FALSE , "FALSE", "8","global"));
   }
}

/******************************************/
/* NAME:	unget_error               */
/* INPUT:       a pointer to token stream */
/* OUTPUT: 	print error message       */
/******************************************/
static unget_error(fp)
character_stream *fp;
{
  _i_function("unget_error");
  _i_node("0");
  _i_def(fp , "fp", "0");
fprintf(stdout,"It can not get charcter\n");
}

/*************************************************/
/* NAME:        print_spec_symbol                */
/* INPUT:       a pointer to a spec_symbol token */
/* OUTPUT :     print out the spec_symbol token  */
/*              according to the form required   */
/*************************************************/
static void print_spec_symbol(str)
token str;
{
_i_function("print_spec_symbol");
_i_node("0");
_i_def(str , "str", "0");
    if(_i_node("1") &&(!strcmp(_i_puse(str , "str"),"(")))
    {
      _i_loc("1", "2");
      _i_node("2");
             fprintf(stdout, "%s\n","lparen.");
             return;
    }else{
      _i_loc("1", "3");
      _i_node("3");
    }

    if (_i_node("4") && (!strcmp(_i_puse(str , "str"),")")))
    {
      _i_loc("4", "5");
      _i_node("5");
             fprintf(stdout, "%s\n","rparen.");
             return;
    }else{
      _i_loc("4", "6");
      _i_node("6");
    }
    if (_i_node("7") && (!strcmp(_i_puse(str , "str"),"[")))
    {
      _i_loc("7", "8");
      _i_node("8");
             fprintf(stdout, "%s\n","lsquare.");
             return;
    }else{
      _i_loc("7", "9");
      _i_node("9");
    }

    if (_i_node("10") && (!strcmp(_i_puse(str , "str"),"]")))
    {
      _i_loc("10", "11");
      _i_node("11");
             fprintf(stdout, "%s\n","rsquare.");
             return;
    }else{
      _i_loc("10", "12");
      _i_node("12");
    }

    if (_i_node("13") && (!strcmp(_i_puse(str , "str"),"'")))
    {
      _i_loc("13", "14");
      _i_node("14");
             fprintf(stdout, "%s\n","quote.");
             return;
    }else{
      _i_loc("13", "15");
      _i_node("15");
    }
    if (_i_node("16") && (!strcmp(_i_puse(str , "str"),"`")))
    {
      _i_loc("16", "17");
      _i_node("17");
             fprintf(stdout, "%s\n","bquote.");
             return;
    }else{
      _i_loc("16", "18");
      _i_node("18");
    }

     fprintf(stdout, "%s\n","comma.");
}


/*************************************/
/* NAME:        is_spec_symbol       */
/* INPUT:       a pointer to a token */
/* OUTPUT:      a BOOLEAN value      */
/*************************************/
static int is_spec_symbol(str)
    token str;
{
  _i_function("is_spec_symbol");
  _i_node("0");
  _i_def(str , "str", "0");

    if (_i_node("1") && (!strcmp(_i_puse(str , "str"),"(")))
    {
      _i_loc("1", "2");
      _i_node("2");
        return(_i_cuse(TRUE , "TRUE", "2","global"));
    }else{
      _i_loc("1", "3");
      _i_node("3");
    }

    if (_i_node("4") && (!strcmp(_i_puse(str , "str"),")")))
    {
      _i_loc("4", "5");
      _i_node("5");
        return(_i_cuse(TRUE , "TRUE", "5","global"));
    }else{
      _i_loc("4", "6");
      _i_node("6");

    }

    if (_i_node("7") && (!strcmp(_i_puse(str , "str"),"[")))
    {
      _i_loc("7", "8");
      _i_node("8");
        return(_i_cuse(TRUE , "TRUE", "8","global"));
    }else{
      _i_loc("7", "9");
      _i_node("9");
    }

    if (_i_node("10") && (!strcmp(_i_puse(str , "str"),"]")))
    {
      _i_loc("10", "11");
      _i_node("11");
        return(_i_cuse(TRUE , "TRUE", "11","global"));
    }else{
      _i_loc("10", "12");
      _i_node("12");
    }

    if (_i_node("13") && (!strcmp(_i_puse(str , "str"),"'")))
    {
      _i_loc("13", "14");
      _i_node("14");
        return(_i_cuse(TRUE , "TRUE", "14","global"));
    }else{
      _i_loc("13", "15");
      _i_node("15");
    }

    if (_i_node("16") && (!strcmp(str,"`")))
    {
      _i_loc("16", "17");
      _i_node("17");
        return(_i_cuse(TRUE , "TRUE", "17","global"));
    }else{
      _i_loc("16", "18");
      _i_node("18");
    }

    if (_i_node("19") && (!strcmp(_i_puse(str , "str"),",")))
    {
      _i_loc("19", "20");
      _i_node("20");
        return(_i_cuse(TRUE , "TRUE", "20","global"));
    }else{
      _i_loc("20", "21");
      _i_node("21");
    }
    _i_node("22");
    return(_i_cuse(FALSE , "FALSE", "22","global"));     /* others return FALSE */
}
