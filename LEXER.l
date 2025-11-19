NUM [0-9]+
ID [a-zA-Z_][a-zA-Z0-9_]*
SIGN  -
COMMENT "//"

%%
  COMMENT.*  /* ignore */     
 [ \t] /*ignore*/ 

{SIGN}?{NUM} return NUMBER;
{ID} return IDENTIFIER; 

 "+"  return ADD;
"-"  return SUBS;
"*"  return MULT;
"/"  return DIV;

"=" return ASSIGN;

([<>]=?|[!=]=) return LOGICALOPERATOR;

"("  return OPAREN;
")"  return CPAREN;
"{"  return OBRACKET;
"}"  return CBRACKET;
";"  return POINTCOMMA;
"&&" return AND;
"||" return OR;

%%