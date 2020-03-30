
/*  -*- Last-Edit:  Fri Jan 29 11:13:27 1993 by Tarak S. Goradia; -*- */
/* $Log: tcas.c,v $
 * Revision 1.2  1993/03/12  19:29:50  foster
 * Correct logic bug which didn't allow output of 2 - hf
 * */

#include <stdio.h>

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
// #define _i_puse(DATA,...)    (sprintf(_v_temp,"%s %s %s",__VA_ARGS__,__VA_ARGS__,__VA_ARGS__),sscanf(_v_temp,"%s %s %s", _v_par1, _v_par2, _v_par3),printf( "p_use %s.%s %s\n", (strcmp(_v_par1,_v_par2)?_v_par2:_v_function), _v_par1, _v_function), DATA)
// #define _i_loc(NODE1,NODE2)  (NODE1)
// #define _i_scope(LINE)       (sprintf(_v_scope,"%s_%s",_v_function,LINE),_v_scope)
/* --------------- */

#define OLEV 600       /* in feets/minute */
#define MAXALTDIFF 600 /* max altitude difference in feet */
#define MINSEP 300     /* min separation in feet */
#define NOZCROSS 100   /* in feet */
                       /* variables */

typedef int bool;

int Cur_Vertical_Sep;
bool High_Confidence;
bool Two_of_Three_Reports_Valid;

int Own_Tracked_Alt;
int Own_Tracked_Alt_Rate;
int Other_Tracked_Alt;

int Alt_Layer_Value; /* 0, 1, 2, 3 */
int Positive_RA_Alt_Thresh[4];

int Up_Separation;
int Down_Separation;

/* state variables */
int Other_RAC; /* NO_INTENT, DO_NOT_CLIMB, DO_NOT_DESCEND */
#define NO_INTENT 0
#define DO_NOT_CLIMB 1
#define DO_NOT_DESCEND 2

int Other_Capability; /* TCAS_TA, OTHER */
#define TCAS_TA 1
#define OTHER 2

int Climb_Inhibit; /* true/false */

#define UNRESOLVED 0
#define UPWARD_RA 1
#define DOWNWARD_RA 2

void initialize() {
  _i_function("initialize");
  _i_node("0");
  Positive_RA_Alt_Thresh[0] = 400;
  Positive_RA_Alt_Thresh[1] = 500;
  Positive_RA_Alt_Thresh[2] = 640;
  Positive_RA_Alt_Thresh[3] = 740;
  _i_def(Positive_RA_Alt_Thresh[0], "Positive_RA_Alt_Thresh", "0", "global");
}

int ALIM() {
  _i_function("ALIM");
  _i_node("0");
  return _i_cuse(Positive_RA_Alt_Thresh[_i_cuse(Alt_Layer_Value, "Alt_Layer_Value", "0", "global")],"Positive_RA_Alt_Thresh", "0", "global");
}

int Inhibit_Biased_Climb() {
  _i_function("Inhibit_Biased_Climb");

  if (_i_node("0") && _i_puse(Climb_Inhibit, "Climb_Inhibit", "global")) {
    _i_loc("0", "1");
    _i_node("1");
    return _i_cuse(Up_Separation, "Up_Separation", "1", "global") + _i_cuse(NOZCROSS, "NOZCROSS", "1", "global");
  } else {
    _i_loc("0", "2");
    _i_node("2");
    return _i_cuse(Up_Separation, "Up_Separation", "2", "global");
  }
}

bool Non_Crossing_Biased_Climb() {
  _i_function("Non_Crossing_Biased_Climb");
  _i_node("0");
  int upward_preferred;
  int upward_crossing_situation;
  bool result;
  _i_def(upward_preferred, "upward_preferred", "0");
  _i_def(upward_crossing_situation, "upward_crossing_situation", "0");
  _i_def(result, "result", "0");

  _i_node("1");
  upward_preferred = Inhibit_Biased_Climb() > _i_cuse(Down_Separation, "Down_Separation", "1", "global");
  _i_def(upward_preferred, "upward_preferred", "1");
  if (_i_node("2") && (_i_puse(upward_preferred, "upward_preferred"))) {
    _i_loc("2", "3");
    _i_node("3");
    result =
        !(Own_Below_Threat()) ||
        ((Own_Below_Threat()) && (!(_i_cuse(Down_Separation, "Down_Separation",
                                            "3", "global") >= ALIM())));
    _i_def(result, "result", "3");
  } else {
    _i_loc("2", "4");
    _i_node("4");
    result = Own_Above_Threat() &&
             (_i_cuse(Cur_Vertical_Sep, "Cur_Vertical_Sep", "4", "global") >=
              _i_cuse(MINSEP, "MINSEP", "4", "global")) &&
             (_i_cuse(Up_Separation, "Up_Separation", "4", "global") >= ALIM());
    _i_def(result, "result", "4");
  }
  _i_node("5");
  return _i_cuse(result, "result", "5");
}

bool Non_Crossing_Biased_Descend() {
  _i_function("Non_Crossing_Biased_Descend");
  _i_node("0");
  int upward_preferred;
  int upward_crossing_situation;
  bool result;
  _i_def(upward_preferred, "upward_preferred", "0");
  _i_def(upward_crossing_situation, "upward_crossing_situation", "0");
  _i_def(result, "result", "0");
  _i_node("1");
  upward_preferred = Inhibit_Biased_Climb() >
                     _i_cuse(Down_Separation, "Down_Separation", "1", "global");
  _i_def(upward_preferred, "upward_preferred", "1");
  if (_i_node("2") && (_i_puse(upward_preferred, "upward_preferred"))) {
    _i_loc("2", "3");
    _i_node("3");
    result =
        Own_Below_Threat() &&
        (_i_cuse(Cur_Vertical_Sep, "Cur_Vertical_Sep", "3", "global") >=
         _i_cuse(MINSEP, "MINSEP", "3", "global")) &&
        (_i_cuse(Down_Separation, "Down_Separation", "3", "global") >= ALIM());
    _i_def(result, "result", "3");
  } else {
    _i_loc("2", "4");
    _i_node("4");
    result = !(Own_Above_Threat()) ||
             ((Own_Above_Threat()) && (_i_cuse(Up_Separation, "Up_Separation",
                                               "4", "global") >= ALIM()));
    _i_def(result, "result", "4");
  }
  _i_node("5");
  return _i_cuse(result, "result", "5");
}

bool Own_Below_Threat() {
  _i_function("Own_Below_Threat");
  _i_node("0");
  return (_i_cuse(Own_Tracked_Alt, "Own_Tracked_Alt", "0", "global") <
          _i_cuse(Other_Tracked_Alt, "Other_Tracked_Alt", "0", "global"));
}

bool Own_Above_Threat() {
  _i_function("Own_Above_Threat");
  _i_node("0");
  return (_i_cuse(Other_Tracked_Alt, "Other_Tracked_Alt", "0", "global") <
          _i_cuse(Own_Tracked_Alt, "Own_Tracked_Alt", "0", "global"));
}

int alt_sep_test() {
  _i_function("alt_sep_test");
  _i_node("0");
  bool enabled, tcas_equipped, intent_not_known;
  bool need_upward_RA, need_downward_RA;
  int alt_sep;
  _i_def(enabled, "enabled", "0");
  _i_def(tcas_equipped, "tcas_equipped", "0");
  _i_def(intent_not_known, "intent_not_known", "0");
  _i_def(need_upward_RA, "need_upward_RA", "0");
  _i_def(need_downward_RA, "need_downward_RA", "0");
  _i_def(alt_sep, "alt_sep", "0");

  _i_node("1");
  enabled = _i_cuse(High_Confidence, "High_Confidence", "1", "global") &&
            (_i_cuse(Own_Tracked_Alt_Rate, "Own_Tracked_Alt_Rate", "1",
                     "global") <= _i_cuse(OLEV, "OLEV", "1", "global")) &&
            (_i_cuse(Cur_Vertical_Sep, "Cur_Vertical_Sep", "1", "global") >
             _i_cuse(MAXALTDIFF, "MAXALTDIFF", "1", "global"));
  _i_def(enabled, "enabled", "1");

  _i_node("2");
  tcas_equipped =
      _i_cuse(Other_Capability, "Other_Capability", "2", "global") ==
      _i_cuse(TCAS_TA, "TCAS_TA", "2", "global");
  _i_def(tcas_equipped, "tcas_equipped", "2");
  _i_node("3");
  intent_not_known = _i_cuse(Two_of_Three_Reports_Valid,
                             "Two_of_Three_Reports_Valid", "3", "global") &&
                     _i_cuse(Other_RAC, "Other_RAC", "3", "global") ==
                         _i_cuse(NO_INTENT, "NO_INTENT", "3", "global");
  _i_def(intent_not_known, "intent_not_known", "3");
  _i_node("4");
  alt_sep = _i_cuse(UNRESOLVED, "UNRESOLVED", "4", "global");
  _i_def(alt_sep, "alt_sep", "4");

  if (_i_node("5") &&(_i_puse(enabled , "enabled") && ((_i_puse(tcas_equipped , "tcas_equipped") && _i_puse(intent_not_known , "intent_not_known")) || !_i_puse(tcas_equipped , "tcas_equipped")))) {
    _i_loc("5", "6");
    _i_node("6");
    need_upward_RA = Non_Crossing_Biased_Climb() && Own_Below_Threat();
    _i_def(need_upward_RA , "need_upward_RA", "6");
    _i_node("7");
    need_downward_RA = Non_Crossing_Biased_Descend() && Own_Above_Threat();
    _i_def(need_downward_RA , "need_downward_RA", "7");

    if (_i_node("8") &&(_i_puse(need_upward_RA , "need_upward_RA") && _i_puse(need_downward_RA , "need_downward_RA"))) {
      _i_loc("8", "9");
      _i_node("9");
      /* unreachable: requires Own_Below_Threat and Own_Above_Threat
         to both be true - that requires Own_Tracked_Alt < Other_Tracked_Alt
         and Other_Tracked_Alt < Own_Tracked_Alt, which isn't possible */
      alt_sep = _i_cuse(UNRESOLVED , "UNRESOLVED", "9","global");
      _i_def(alt_sep , "alt_sep", "9");
    } else {
      _i_loc("8", "10");
      if (_i_node("10") &&(_i_puse(need_upward_RA , "need_upward_RA"))) {
        _i_loc("10", "11");
        _i_node("11");
        alt_sep = _i_cuse(UPWARD_RA , "UPWARD_RA", "11","global");
        _i_def(alt_sep , "alt_sep", "11");
      } else {
        _i_loc("10", "12");
        if (_i_node("12")&&(_i_puse(need_downward_RA , "need_downward_RA"))) {
          _i_loc("12", "13");
          _i_node("13");
          alt_sep = _i_cuse( DOWNWARD_RA, "DOWNWARD_RA", "13","global");
        } else {
          _i_loc("12", "14");
          _i_node("14");
          alt_sep= _i_cuse(UNRESOLVED , "UNRESOLVED", "14","global");
          _i_def(alt_sep , "alt_sep", "14");
        }
      }
    }
  } else {
    _i_loc("5", "15");
    _i_node("15");
  }
  _i_node("16");
  return _i_cuse(alt_sep , "alt_sep", "16");
}

void global_sets(){
  _i_function("global");
  _i_node("0");
  _i_def( OLEV, "OLEV", "0");
  _i_def( MAXALTDIFF, "MAXALTDIFF", "0");
  _i_def( MINSEP, "MINSEP", "0");
  _i_def( NOZCROSS, "NOZCROSS", "0");
  _i_def( Cur_Vertical_Sep, "Cur_Vertical_Sep", "0");
  _i_def( High_Confidence, "High_Confidence", "0");
  _i_def( Two_of_Three_Reports_Valid, "Two_of_Three_Reports_Valid", "0");
  _i_def( Own_Tracked_Alt, "Own_Tracked_Alt", "0");
  _i_def( Own_Tracked_Alt_Rate, "Own_Tracked_Alt_Rate", "0");
  _i_def( Other_Tracked_Alt, "Other_Tracked_Alt", "0");
  _i_def( Alt_Layer_Value, "Alt_Layer_Value", "0");
  _i_def( Positive_RA_Alt_Thresh, "Positive_RA_Alt_Thresh", "0");
  _i_def( Up_Separation, "Up_Separation", "0");
  _i_def( Down_Separation, "Down_Separation", "0");
  _i_def( Other_RAC, "Other_RAC", "0");
  _i_def( NO_INTENT, "NO_INTENT", "0");
  _i_def( DO_NOT_CLIMB, "DO_NOT_CLIMB", "0");
  _i_def( DO_NOT_DESCEND, "DO_NOT_DESCEND", "0");
  _i_def( Other_Capability, "Other_Capability", "0");
  _i_def( TCAS_TA, "TCAS_TA", "0");
  _i_def( OTHER, "OTHER", "0");
  _i_def( Climb_Inhibit, "Climb_Inhibit", "0");
  _i_def( UNRESOLVED, "UNRESOLVED", "0");
  _i_def( UPWARD_RA, "UPWARD_RA", "0");
  _i_def( DOWNWARD_RA, "DOWNWARD_RA", "0");

}

main(argc, argv) int argc;
char *argv[];
{
  global_sets();
  _i_function("main");
  _i_node("0");
  _i_def(argc , "argc", "0");
  _i_def(argv , "argv", "0");


  if (_i_node("1") && (_i_puse(argc , "argc") < 13)) {
    _i_loc("1", "2");
    _i_node("2");
    fprintf(stdout, "Error: Command line arguments are\n");
    fprintf(stdout,
            "Cur_Vertical_Sep, High_Confidence, Two_of_Three_Reports_Valid\n");
    fprintf(stdout,
            "Own_Tracked_Alt, Own_Tracked_Alt_Rate, Other_Tracked_Alt\n");
    fprintf(stdout, "Alt_Layer_Value, Up_Separation, Down_Separation\n");
    fprintf(stdout, "Other_RAC, Other_Capability, Climb_Inhibit\n");
    exit(1);
  }else{
    _i_loc("1", "3");
    _i_node("3");
  }
  _i_node("4");
  initialize();

  _i_node("5");
  Cur_Vertical_Sep = atoi(_i_cuse(argv[1] , "argv", "5"));
  _i_def(Cur_Vertical_Sep , "Cur_Vertical_Sep", "5","global");

  _i_node("6");
  High_Confidence = atoi(_i_cuse(argv[2], "argv", "6"));
  _i_def(High_Confidence , "High_Confidence", "6","global");

  _i_node("7");
  Two_of_Three_Reports_Valid = atoi(_i_cuse(argv[3], "argv", "7"));
  _i_def(Two_of_Three_Reports_Valid , "Two_of_Three_Reports_Valid", "7","global");

_i_node("8");
  Own_Tracked_Alt = atoi(_i_cuse(argv[4], "argv", "8"));
  _i_def(Own_Tracked_Alt , "Own_Tracked_Alt", "8","global");

  _i_node("9");
  Own_Tracked_Alt_Rate = atoi(_i_cuse(argv[5], "argv", "9"));
  _i_def(Own_Tracked_Alt_Rate , "Own_Tracked_Alt_Rate", "9","global");

  _i_node("10");
  Other_Tracked_Alt = atoi(_i_cuse(argv[6], "argv", "10"));
  _i_def(Other_Tracked_Alt , "Other_Tracked_Alt", "10","global");


  _i_node("11");
  Alt_Layer_Value = atoi(_i_cuse(argv[7], "argv", "11"));
  _i_def(Alt_Layer_Value , "Alt_Layer_Value", "11","global");

  _i_node("12");
  Up_Separation = atoi(_i_cuse(argv[8], "argv", "12"));
  _i_def(Up_Separation , "Up_Separation", "12","global");

  _i_node("13");
  Down_Separation = atoi(_i_cuse(argv[9], "argv", "13"));
  _i_def(Down_Separation , "Down_Separation", "13","global");

  _i_node("14");
  Other_RAC = atoi(_i_cuse(argv[10], "argv", "14"));
  _i_def(Other_RAC , "Other_RAC", "14","global");

  _i_node("15");
  Other_Capability = atoi(_i_cuse(argv[11], "argv", "15"));
  _i_def(Other_Capability , "Other_Capability", "15","global");

  _i_node("16");
  Climb_Inhibit = atoi(_i_cuse(argv[12], "argv", "16"));
  _i_def(Climb_Inhibit , "Climb_Inhibit", "16","global");

  _i_node("17");
  fprintf(stdout, "%d\n", alt_sep_test());
  exit(0);
}
