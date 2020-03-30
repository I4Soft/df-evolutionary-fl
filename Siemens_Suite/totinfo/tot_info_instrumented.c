/*
	tot_info -- combine information statistics for multiple tables

	last edit:	89/02/06	D A Gwyn

	SCCS ID:	@(#)tot_info.c	1.1 (edited for publication)
*/

#include	<ctype.h>
#include	<stdio.h>

#include	"std.h"

#include	"chisq.h"
#include	"gamma.h"		/* for QChiSq() */


#define	MAXLINE	256


#ifndef MAXTBL
#define	MAXTBL	1000
#endif

static char	line[MAXLINE];		/* row/column header input line */
static long	f[MAXTBL];		/* frequency tallies */
static int	r;			/* # of rows */
static int	c;			/* # of columns */

#define	x(i,j)	f[(i)*c+(j)]		/* convenient way to access freqs */

#define	COMMENT	'#'			/* comment character */


#ifndef NULL
#define NULL 0
#endif

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
void global_sets(){
	_i_function("global");
	_i_node("0");
	_i_def(MAXLINE , "MAXLINE", "0");
	_i_def(MAXTBL , "MAXTBL", "0");
	_i_def(1 , "ITMAX", "0");
	_i_def(1 , "EPS", "0");
	_i_cuse(MAXLINE , "MAXLINE", "0");
	_i_def(line , "line", "0");
	_i_cuse(MAXTBL , "MAXTBL", "0");
	_i_def(f , "f", "0");
	_i_def(r , "r", "0");
	_i_def(c , "c", "0");
}
/*ARGSUSED*/
int
main( argc, argv )
	int		argc;
	char		*argv[];
	{
	global_sets();


	_i_function("main");
	_i_node("0");
	_i_def(argc,"argc","0");
	_i_def(argv,"argv","0");
	_i_node("1");
	char	*p;		/* input line scan location */
	int	i;		/* row index */
	int	j;		/* column index */
	double		info;		/* computed information measure */
	int		infodf;		/* degrees of freedom for information */
	double		totinfo = 0.0;	/* accumulated information */
	int		totdf;	/* accumulated degrees of freedom */

        totdf = 0;
	_i_def(p,"p","1");
	_i_def(i,"i","1");
	_i_def(j,"j","1");
	_i_def(info,"info","1");
	_i_def(infodf,"infodf","1");
	_i_def(totinfo,"totinfo","1");
	_i_def(totdf,"totdf","1");
	while ( _i_node("2") && (fgets( line, _i_puse(MAXLINE,"MAXLINE","global"), stdin ) != NULL ))	/* start new table */
		{
		_i_def(line,"line","2","global");
		_i_loc("2","3");
		for ( _i_node("3"),p = _i_cuse(line,"line","3","global"),_i_def(p,"p","3"); _i_node("4") && (_i_puse(*p,"p") != '\0' && isspace( (int)_i_puse(*p,"p") )); _i_node("6"),_i_cuse(_i_def(_i_cuse(++p, "p", "6"), "p", "6") , "p", "6"))
            {
			_i_loc("4","5");
			_i_node("5");
			}
		_i_loc("4","7");
		_i_node("7");
		if ( _i_node("8") && (_i_puse(*p,"p") == '\0') )
		{
			_i_loc("8","9");
			_i_node("9");
			continue;	/* skip blank line */
		}
		_i_loc("8","10");
		_i_node("10");
		if ( _i_node("11") && (_i_puse(*p,"p") == _i_puse(COMMENT,"COMMENT","global") ) )
			{		/* copy comment through */
			_i_loc("11","12");
			_i_node("12");
			(void)fputs( _i_cuse(line,"line","12","global"), stdout );
			continue;
			}
		_i_loc("11","13");
		_i_node("13");
		if ( _i_node("14") && (sscanf( _i_puse(p,"p"), "%d %d\n", _i_def(&r,"r","14","global"), _i_def(&c,"c","14","global") ) != 2 ))
			{
			_i_loc("14","15");
			_i_node("15");
			(void)fputs( "* invalid row/column line *\n", stdout );
			_i_node("16");
			return _i_cuse(EXIT_FAILURE,"EXIT_FAILURE","16","global");
			}
		_i_loc("14","17");
		_i_node("17");
		if ( _i_node("18") && (_i_puse(r,"r","global") * _i_puse(c,"c","global") > _i_puse(MAXTBL,"MAXTBL","global")) )
			{
			_i_loc("18","19");
			_i_node("19");
			(void)fputs( "* table too large *\n", stdout );
			_i_node("20");
			return _i_cuse(EXIT_FAILURE,"EXIT_FAILURE","20","global");
			}
		_i_loc("18","21");
		_i_node("21");
		/* input tallies */
		for ( _i_node("22"), i = 0, _i_def(i,"i","22");
			_i_node("23") && (_i_puse(i,"i") < _i_puse(r,"r","global"));
			_i_node("34"), _i_cuse(_i_def(_i_cuse(++i, "i", "34"), "i", "34") , "i", "34") )
		{
			_i_loc("23","24");
			_i_node("24");
			for ( _i_node("25"), j = 0, _i_def(j,"j","25");
				_i_node("26") && (_i_puse(j,"j") < _i_puse(c,"c","global"));
				_i_node("32"),_i_cuse(_i_def(_i_cuse(++j, "j", "32"), "j", "32") , "j", "32") )
			{
				_i_loc("26","27");
				_i_node("27");
				if ( _i_node("28") &&
					( scanf( " %ld",
						_i_puse(&f[(_i_cuse(i,"i","28"))*_i_cuse(c,"c","28","global")+(_i_cuse(j,"j","28"))],"f","global")
						) ) != 1 )
					{
					_i_loc("28","29");
					_i_node("29");
					(void)fputs( "* EOF in table *\n",
						     stdout
						   );
					_i_node("30");
					return _i_cuse(EXIT_FAILURE,"EXIT_FAILURE","30","global");
					}
				_i_loc("28","31");
				_i_node("31");
			}
			_i_loc("26","33");
			_i_node("33");
		}
		_i_loc("23","35");
		_i_node("35");
		/* compute statistic */
		_i_node("36");
		info = InfoTbl( _i_cuse(r,"r","36","global"), _i_cuse(c,"c","36","global"),
				_i_cuse(f,"f","36","global"), _i_cuse(&infodf,"infodf","36") );
    _i_def( info, "info", "36");


		/* print results */

		if ( _i_node("37") && (_i_puse(info,"info") >= 0.0) )
			{
			_i_loc("37","38");
			_i_node("38");
			(void)printf( "2info = %5.2f\tdf = %2d\tq = %7.4f\n",
				      _i_cuse(info,"info","38"), _i_cuse(infodf,"infodf","38"),
				      QChiSq( _i_cuse(info,"info","38"), _i_cuse(infodf,"infodf","38") )
				    );
			_i_node("39");
			totinfo = _i_cuse(totinfo,"totinfo","39") + _i_cuse(info,"info","39");
			_i_def(totinfo,"totinfo","39");
			_i_node("40");
			totdf = _i_cuse(totdf,"totdf","40") + _i_cuse(infodf,"infodf","40");
			_i_def(totdf,"totdf","40");
			}
		else
			{
			_i_loc("37","41");
			_i_node("41");
			if ( _i_node("42") && (_i_puse(info,"info") < -3.5) )
				{
				_i_loc("42","43");
				_i_node("43");
				(void)fputs("out of memory\n", stdout);
				}
			else
				{
				_i_loc("42","44");
				_i_node("44");
				if ( _i_node("45") && (_i_puse(info,"info") < -2.5) )
					{
					_i_loc("45","46");
					_i_node("46");
					(void)fputs("table too small\n", stdout);
					}
				else
					{
					_i_loc("45","47");
					_i_node("47");
					if ( _i_node("48") && (_i_puse(info,"info") < -1.5) )
						{
						_i_loc("48","49");
						_i_node("49");
						(void)fputs("negative freq\n", stdout);
						}
					else
						{
						_i_loc("48","50");
						_i_node("50");
						(void)fputs("table all zeros\n", stdout);
						}
					}
				}
			}
		}
	_i_def(line,"line","2","global");
	_i_loc("2","51");
	_i_node("51");
	if ( _i_node("52") && ( _i_puse(totdf, "totdf") <= 0 ) )
		{
		_i_loc("52","53");
		_i_node("53");
		(void)fputs( "\n*** no information accumulated ***\n", stdout );
		_i_node("54");
		return _i_cuse(EXIT_FAILURE,"EXIT_FAILURE","54","global");
		}
	_i_loc("52","55");
	_i_node("55");
	(void)printf( "\ntotal 2info = %5.2f\tdf = %2d\tq = %7.4f\n",
		      _i_cuse(totinfo,"totinfo","55"), _i_cuse(totdf,"totdf","55"),
		      QChiSq( _i_cuse(totinfo,"totinfo","55"), _i_cuse(totdf,"totdf","55") )
		    );
	}


/*  -*- Last-Edit:  Tue Dec 15 14:48:14 1992 by Tarak S. Goradia; -*- */

/*
	Gamma -- gamma and related functions

	last edit:	88/09/09	D A Gwyn

	SCCS ID:	@(#)gamma.c	1.1 (edited for publication)

Acknowledgement:
	Code based on that found in "Numerical Methods in C".
*/

#include	<math.h>
#include        <stdio.h>

#include	"std.h"

double
LGamma( x )
	double			x;
	{
	_i_function("LGamma");
	_i_node("0");
	_i_def(x,"x","0");
	_i_node("1");
	static const double	cof[6] =
		{
		76.18009173,	-86.50532033,	24.01409822,
		-1.231739516,	0.120858003e-2,	-0.536382e-5
		};
	double			tmp, ser;
	int		j;
	_i_def(cof,"cof","1");
	_i_def(tmp,"tmp","1");
	_i_def(ser,"ser","1");
	_i_def(j,"j","1");

	if (_i_node("2") && (_i_puse( _i_cuse(_i_def(_i_cuse(--x, "x", "2"), "x", "2") , "x", "2"), "x") < 0.0) )	/* use reflection formula for accuracy */
		{
		_i_loc("2","3");
		_i_node("3");
		double	pix = _i_cuse(PI,"PI","3","global") * _i_cuse(x,"x","3");
		_i_def(pix,"pix","3",_i_scope("282"));
		_i_node("4");
		return log( _i_cuse(pix,"pix","4",_i_scope("282")) /
				sin( _i_cuse(pix,"pix","4",_i_scope("282")) ) ) - LGamma( 1.0 - _i_cuse(x,"x","4") );
		}
	_i_loc("2","5");
	_i_node("5");
	tmp = _i_cuse(x,"x","5") + 5.5;
	_i_def(tmp,"tmp","5");
	_i_node("6");
	tmp = _i_cuse(tmp,"tmp","6") - ( (_i_cuse(x,"x","6") + 0.5) * log( _i_cuse(tmp,"tmp","6") ) );
	_i_def(tmp,"tmp","6");
	_i_node("7");
	ser = 1.0;
	_i_def(ser,"ser","7");
	for ( _i_node("8") , j = 0 ;
		_i_node("9") && (_i_puse(j,"j","9") < 6);
		_i_node("11"), _i_cuse(_i_def(_i_cuse(++j, "j", "11"), "j", "11") , "j", "11") )
		{
		_i_loc("9","10");
		_i_node("10");

		_i_cuse(ser,"ser","10");
		ser += _i_cuse(cof[_i_cuse(j , "j", "10")] , "cof", "10") / _i_cuse(_i_def(_i_cuse(++x, "x", "10"), "x", "10") , "x", "10");
		_i_def(ser,"ser","10");
		}
	_i_loc("9","12");
	_i_node("12");
	_i_node("13");
	return -_i_cuse(tmp,"tmp","13") + log( 2.50662827465 * _i_cuse(ser,"ser","13") );
	}

#define	ITMAX	100
#define	EPS	3.0e-7

static double
gser( a, x )
	double		a, x;
	{
	_i_function("gser");
	_i_node("0");
	_i_def(a, "a", "0");
	_i_def(x, "x", "0");
	_i_node("1");
	double		ap, del, sum;
	_i_def(ap , "ap", "1");
	_i_def(del , "del", "1");
	_i_def(sum , "sum", "1");
	int	n;
	_i_def(n , "n", "1");

	if (_i_node("2") && (_i_puse(x , "x") <= 0.0) ){
		_i_loc("2" , "3");
		_i_node("3");
		return 0.0;
	}
	else{
		_i_loc("2" , "4");
		_i_node("4");

	}
	_i_node("5");

	ap = _i_cuse(a , "a", "5");
	_i_def(ap , "ap", "ap");
	sum = 1.0/_i_cuse(ap , "ap", "5");
	_i_def(sum , "sum", "5");
	del = _i_cuse(sum , "sum", "5");
	_i_def(del , "del", "5");

	for ( _i_node("6"), n = 1,_i_def(n , "n", "6");_i_node("7")&& (_i_puse(n , "n") <= _i_puse(ITMAX ,"ITMAX", "global"));_i_node("12"),_i_cuse(_i_def(_i_cuse(++n, "n", "12"), "n", "12") , "n", "12") )
		{
			_i_loc("7" , "8");
			_i_node("8");
			_i_cuse(del , "del", "8");
			del *= _i_cuse(x , "x", "8") / _i_cuse(_i_def(_i_cuse(++ap, "ap", "8"), "ap", "8") , "ap", "8");
			_i_def(del , "del", "8");
			_i_cuse(sum , "sum", "8");
			sum += _i_cuse(del , "del", "8");
			_i_def(sum , "sum", "8");

			if (_i_node("9") && (Abs( _i_puse(del , "del")) < Abs( _i_puse(sum , "sum") ) * _i_puse(EPS , "EPS","global"))){
				_i_loc("9" , "10");
				_i_node("10");
				return _i_cuse(sum , "sum", "10")* exp( -_i_cuse(x , "x", "10") + _i_cuse(a , "a", "10") * log( _i_cuse(x , "x", "10")) - LGamma( _i_cuse(a , "a", "10")  ) );
			}
			else{
				_i_loc("9" , "11");
				_i_node("11");
			}
		}
		_i_loc("7" , "3");
		_i_node("13");
	/*NOTREACHED*/
	}

static double
gcf( a, x )
	double		a, x;
	{
	_i_function("gcf");
	_i_node("0");
	_i_def(a , "a", "0");
	_i_def(x , "x", "0");
	_i_node("1");
	int	n;
	_i_def(n , "1", "1");

	double		gold = 0.0, fac = 1.0, b1 = 1.0,
			b0 = 0.0, a0 = 1.0;
	_i_def(gold , "gold", "1");
	_i_def(fac , "fac", "1");
	_i_def(b1 , "b1", "1");
	_i_def(b0 , "b0", "1");
	_i_def(a0 , "a0", "1");
	double a1 = _i_cuse(x , "x", "1");
	_i_def(a1 , "a1", "1");

	for (_i_node("2"), n = 1,_i_def(n , "n", "2");_i_node("3")&& (_i_puse(n , "n") <= _i_puse(ITMAX , "ITMAX","global"));_i_node("20"), _i_cuse(_i_def(_i_cuse(++n, "n", "20"), "n", "20") , "n", "20")  )
		{
			_i_loc("3" , "4");
			_i_node("4");
		double	anf;
		_i_def(anf , "anf", "4", _i_scope("405"));
		_i_node("5");
		double	an = (double)_i_cuse(n , "n", "5");
		_i_def(an , "an", "5",_i_scope("408"));
		_i_function("6");
		double	ana = _i_cuse(an , "an", "6",_i_scope("408")) - _i_cuse(a , "a", "6");
		_i_def(ana , "ana", "6",_i_scope("411"));
		_i_node("7");
		a0 = (_i_cuse(a1 , "a1", "7") + _i_cuse(a0 , "a0", "7") * _i_cuse(ana , "ana", "7",_i_scope("411"))) * _i_cuse(fac , "fac", "7");
		_i_def(a0 , "a0", "7");
		_i_node("8");
		b0 = (_i_cuse(b1 , "b1", "8") + _i_cuse(b0 , "b0", "8") * _i_cuse(ana , "ana", "8",_i_scope("411"))) * _i_cuse(fac , "fac", "8");
		_i_def(b0 , "b0", "8");
		_i_node("9");
		anf = _i_cuse(an , "an", "9",_i_scope("408")) * _i_cuse(fac , "fac", "9");
		_i_def(anf , "anf", "9",_i_scope("405"));
		_i_node("10");
		b1 = _i_cuse(x , "x", "10") * _i_cuse(b0 , "b0", "10") + _i_cuse(anf , "anf", "10",_i_scope("405")) * _i_cuse(b1 , "b1", "10");
		_i_def(b1 , "b1", "10");
		_i_node("11");
		a1 = _i_cuse(x , "x", "11") * _i_cuse(a0 , "a0", "11") + _i_cuse(anf , "anf", "11",_i_scope("405")) * _i_cuse(a1 , "a1", "11");
		_i_def(a1 , "a1", "11");


			if (_i_node("12") && (_i_puse(a1 , "a1") != 0.0) )
				{		/* renormalize */
					_i_loc("12" , "13");
					_i_node("13");
					fac = 1.0 / _i_cuse(a1 , "a1", "13");
					_i_def(fac , "fac", "13");
				double	g = _i_cuse(b1 , "b1", "13") * _i_cuse(fac , "fac", "13");
				_i_def(g , "g", "13",_i_scope("436"));

				_i_node("14");
				gold = _i_cuse(g , "g", "14",_i_scope("436")) - _i_cuse(gold , "gold", "14");
				_i_def(gold , "gold", "14");

				if (_i_node("15")&& Abs( _i_puse(gold , "gold") ) < _i_puse(EPS , "EPS","global") * Abs( _i_puse(g , "g",_i_scope("436")) ) ){
					_i_loc("15" , "16");
					_i_node("16");
					return exp( -_i_cuse(x , "x", "16") + _i_cuse(a , "a", "16") * log( _i_cuse(x , "x", "16") ) - LGamma( _i_cuse(a , "a", "16") ) ) * _i_cuse(g , "g", "16",_i_scope("436"));
				}else{
					_i_loc("15" , "17");
					_i_node("17");
				}
				_i_node("18");
				gold = _i_cuse(g , "g", "18","436");
				_i_def(gold , "gold", "18");
			}else{
				_i_loc("12" , "19");
				_i_node("19");
			}
		}
		_i_loc("" , "21");
		_i_node("21");

	/*NOTREACHED*/
	}

double
QGamma( a, x )
	double	a, x;
	{
		_i_function("Qgamma");
		_i_node("0");
		_i_def(a , "a", "0");
		_i_def(x , "x", "0");

		if (_i_node("1") && (_i_puse(x , "x") < _i_puse(a , "a") + 1.0)) {
			_i_loc("1" , "2");
			_i_node("2");
			return  1.0 - gser( _i_cuse(a , "a", "2"), _i_cuse(x , "x", "2") );
		}
		else{
			_i_loc("1" , "3");
			_i_node("3");
			return  gcf( _i_cuse(a , "a", "3"), _i_cuse(x , "x", "3") );
		}

	}

double
QChiSq( chisq, df )
	double	chisq;
	int	df;
	{
		_i_function("QChisq");
		_i_node("0");
		_i_def(chisq , "chisq", "0");
		_i_def(df , "df", "0");
		_i_node("1");
	return QGamma( (double)_i_cuse(df , "df", "1") / 2.0, _i_cuse(chisq , "chisq", "1") / 2.0 );
	}


/*
	InfoTbl -- Kullback's information measure for a 2-way contingency table

	last edit:	88/09/19	D A Gwyn

	SCCS ID:	@(#)info.c	1.1 (edited for publication)

	Special return values:
		-1.0	entire table consisted of 0 entries
		-2.0	invalid table entry (frequency less than 0)
		-3.0	invalid table dimensions (r or c less than 2)
		-4.0	unable to allocate enough working storage
*/

#include	<math.h>		/* for log() */
#if __STDC__
#include	<stdlib.h>		/* malloc, free */

#include	"std.h"
#else
#include	"std.h"

extern pointer	malloc();
extern void	free();
#endif

#ifndef NULL
#define NULL 0
#endif

#define	x(i,j)	f[(i)*c+(j)]		/* convenient way to access freqs */

double
InfoTbl( r, c, f, pdf )
	int		r;		/* # rows in table */
	int		c;		/* # columns in table */
	const long	*f;		/* -> r*c frequency tallies */
	int		*pdf;		/* -> return # d.f. for chi-square */
	{
	_i_function("InfoTbl");
	_i_node("0");
	_i_def(r , "r", "0");
	_i_def(c , "c", "0");
	_i_def(f , "f", "0");
	_i_def(pdf , "pdf", "0");

	_i_node("1");
	int	i;		/* row index */
	int	j;		/* column index */
	double		N;		/* (double)n */
	double		info;		/* accumulates information measure */
	double		*xi;		/* row sums */
	double		*xj;		/* col sums */
	_i_def(i , "i", "1");
	_i_def(j , "j", "1");
	_i_def(N , "N", "1");
	_i_def(info , "info", "1");
	_i_def(xi , "xi", "1");
	_i_def(xj , "xj", "1");

	_i_node("2");
	int		rdf = _i_cuse(r , "r", "2") - 1;	/* row degrees of freedom */
	_i_def(rdf , "rdf", "2");

	_i_node("3");
	int		cdf = _i_cuse(c , "c", "3") - 1;	/* column degrees of freedom */
_i_def(cdf , "cdf", "3");
	if (_i_node("4") && (_i_puse(rdf , "rdf") <= 0 || _i_puse(cdf , "cdf") <= 0) )
		{
			_i_loc("4" , "5");
			_i_node("5");
		info = -3.0;
		_i_def(info , "info", "5");
		_i_node("6");
		goto ret3;
		}
		else{
			_i_loc("4" , "7");
			_i_node("7");
		}
		_i_node("8");
		*pdf = _i_cuse(rdf , "rdf", "8") * _i_cuse(cdf , "cdf", "8");		/* total degrees of freedom */
		_i_def(pdf , "pdf", "8");
	if (_i_node("9")&& (_i_puse( _i_def( (xi = (double *)malloc( r * sizeof(double) )), "xi", "9") , "9")== NULL ))
		{
			_i_loc("9" , "10");
			_i_node("10");
		info = -4.0;
		_i_def(info , "info", "10");
		_i_node("11");
		goto ret3;
	}else{
		_i_loc("9" , "12");
		_i_node("12");
	}

	if (_i_node("13") &&( _i_puse( _i_def(  (xj = (double *)malloc( c * sizeof(double) )), "xj", "13"), "xj") == NULL))
		{
			_i_loc("13", "14");
			_i_node("14");
		info = -4.0;
		_i_def(info , "info", "14");
		_i_node("15");
		goto ret2;
		}
		else{
			_i_loc("13" , "16");
			_i_node("16");
		}

	/* compute row sums and total */
		_i_node("17");
		N = 0.0;
		_i_def(N , "N", "17");

	for (_i_node("18"), i = 0, _i_def(i , "i", "18"); _i_node("19") && (_i_puse(i , "i") < _i_puse(r , "r"));_i_node("31"), _i_cuse(_i_def(_i_cuse(++i, "i", "31"), "i", "31") , "i", "31") )
		{
			_i_loc("19" , "20");
			_i_node("20");
		double	sum = 0.0;	/* accumulator */
		_i_def(sum , "sum", "20",_i_scope("619"));
		for (_i_node("21"), j = 0, _i_def(j , "j", "21");_i_node("22") && (_i_puse(j , "j") < _i_puse(c , "c")); _i_node("29"), _i_cuse(_i_def(_i_cuse(++j, "j", "29"), "j", "29") , "j", "29")  )
			{
				_i_loc("22" , "23");
				_i_node("23");
				long	k = _i_cuse( f[(_i_cuse(i , "i", "23"))*_i_cuse(c , "c", "23")+(_i_cuse(j , "j", "23"))], "f", "23");
				_i_def(k , "k", "23", _i_scope("624"));
			if (_i_node("24")&& (_i_puse(k , "k") < 0L) )
				{
					_i_loc("24" , "25");
					_i_node("25");
				info = -2.0;
				_i_def(info , "info", "25");
				_i_node("26");
				goto ret1;
			}else{
				_i_loc("24" , "27");
				_i_node("27");
			}
			_i_node("28");
			sum += (double)_i_cuse(k , "k", "28","624");
			_i_def(sum , "sum", "28",_i_scope("619"));
			}
			_i_loc("22" , "30");
			_i_node("30");
			xi[_i_cuse(i , "i", "30")] = _i_cuse(sum , "sum", "30",_i_scope("619"));
			_i_def(xi , "xi", "30");
			_i_cuse(N , "N", "30");
		N += _i_cuse(xi[_i_cuse(i , "i", "30")] , "xi", "30");
		_i_def(N , "N", "30");
		}
		_i_loc("19" , "32");
		_i_node("32");

	if (_i_node("33")&& (_i_puse(N , "N") <= 0.0) )
		{
			_i_loc("33" , "34");
		_i_node("34");
		info = -1.0;
		_i_def(info , "info", "34");
		_i_node("35");
		goto ret1;
		}
	else{
		_i_loc("33" , "36");
		_i_node("36");
	}

	/* compute column sums */

	for (_i_node("37"), j = 0, _i_def(j , "j", "37");_i_node("38")&& (_i_puse(j , "j") < _i_puse(c , "c"));_i_node("45"), _i_cuse(_i_def(_i_cuse(++j, "j", "45"), "j", "45") , "j", "45"))
		{
			_i_loc("38" , "39");
			_i_node("39");
		double	sum = 0.0;	/* accumulator */
			_i_def(sum , "sum", "39",_i_scope("674"));

		for (_i_node("40"), i = 0,_i_def(i, "i", "40");_i_node("41")&& (_i_puse(i , "i") < _i_puse(r , "r"));_i_node("43"),  _i_cuse(_i_def(_i_cuse(++i, "i", "43"), "i", "43") , "i", "43") ){
			_i_loc("41" , "42");
			_i_node("42");
			sum += (double)_i_cuse( f[(_i_cuse(i , "i", "42"))*_i_cuse(c , "c", "42")+(_i_cuse(j , "j", "42"))], "f", "42");
			_i_def(sum , "sum", "42",_i_scope("674"));
		}
		_i_loc("41" , "44");
		_i_node("44");
		xj[_i_cuse(j , "j", "44")] = _i_cuse(sum , "sum", "44",_i_scope("674"));
		_i_def(xj , "xj", "44");
		}
		_i_loc("38" , "46");
		_i_node("46");

	/* compute information measure (four parts) */

	info = _i_cuse(N , "N", "46") * log( _i_cuse(N , "N", "46") );					/* part 1 */
	_i_def(info , "info", "46");
	for (_i_node("47"), i = 0,_i_def(i , "i", "47");_i_node("48")&& (_i_puse(i , "i") < _i_puse(r , "r")) ;_i_node("61"), _i_cuse(_i_def(_i_cuse(++i, "i", "61"), "i", "61") , "i", "61") )
		{
			_i_loc("48" , "49");
			_i_node("49");
		double	pi = _i_cuse( xi[_i_cuse(i , "i", "49")], "xi", "49");	/* row sum */
			_i_def(pi , "pi", "49",_i_scope("699"));
		if (_i_node("50")&& (_i_puse(pi , "pi",_i_scope("699")) > 0.0) ){
			_i_loc("50" , "51");
			_i_node("51");
			_i_cuse(info , "info", "51");
			info -= _i_cuse(pi , "pi", "51",_i_scope("699")) * log( _i_cuse(pi , "pi", "51",_i_scope("699")) );			/* part 2 */
			_i_def(info , "info", "51");
		}
		else{
			_i_loc("50" , "52");
			_i_node("52");

		}

		for (_i_node("53"), j = 0,_i_def(j , "j", "53");_i_node("54")&& (_i_puse(j , "j") < _i_puse(c , "c"));_i_node("59"), _i_cuse(_i_def(_i_cuse(++j, "j", "59"), "j", "59") , "j", "59") )
			{
				_i_loc("54" , "55");
				_i_node("55");
			double	pij = (double)_i_cuse(f[(_i_cuse(i , "i", "55"))*_i_cuse(c , "c", "55")+(_i_cuse(j , "j", "55"))] , "f", "55");
				_i_def(pij , "pij", "55",_i_scope("718"));
				if (_i_node("56")&& (_i_puse(pij , "pij",_i_scope("718")) > 0.0) ){
					_i_loc("56" , "57");
					_i_node("57");
					_i_cuse(info , "info", "57");
					info += _i_cuse(pij , "pij", "57",_i_scope("718")) * log( _i_cuse(pij , "pij", "57",_i_scope("718")) );	/* part 3 */
					_i_def(info , "info", "57");
				}else{
					_i_loc("56" , "58");
					_i_node("58");
				}
			}
			_i_loc("54" , "60");
			_i_node("60");
		}
		_i_loc("48" , "62");
		_i_node("62");

	for (_i_node("63"), j = 0,_i_def(j , "j", "63");_i_node("64")&& (_i_puse(j , "j") < _i_puse(c , "c"));_i_node("69"), _i_cuse(_i_def(_i_cuse(++j, "j", "69"), "j", "69") , "j", "69") )
		{
			_i_loc("64" , "65");
			_i_node("65");
		double	pj = _i_cuse(xj[_i_cuse(j , "j", "65")] , "xj", "65");	/* column sum */
		_i_def(pj , "pj", "65",_i_scope("741"));

			if (_i_node("66") && (_i_puse(pj , "pj",_i_scope("741")) > 0.0) ){
				_i_loc("66" , "67");
				_i_node("67");
				_i_cuse(info , "info", "67");
				info -= _i_cuse(pj , "pj", "67",_i_scope("741")) * log(_i_cuse(pj , "pj", "67",_i_scope("741"))  );			/* part 4 */
				_i_def(info , "info", "67");
			}else{
				_i_loc("66" , "68");
				_i_node("68");
			}

		}
		_i_loc("64" , "70");
		_i_node("70");
		_i_cuse(info , "info", "70");
	info *= 2.0;			/* for comparability with chi-square */
		_i_def(info , "info", "70");

    ret1:
    _i_node("71");
	free( (pointer)_i_cuse(xj , "xj", "71"));
    ret2:
      _i_node("72");
	free( (pointer)_i_cuse(xi , "xi", "72"));
    ret3:
      _i_node("73");
	return _i_cuse(info , "info", "73");
	}
