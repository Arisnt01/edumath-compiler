grammar EduMath;

programa: instruccion+ EOF;

instruccion
    : expresion ';'
    ;

expresion
    : potencia
    ;

potencia
    : suma ('^' potencia)?
    ;

suma
    : producto (('+' | '-') producto)*
    ;

producto
    : atomo (('*' | '/') atomo)*
    ;

atomo
    : 'raiz' '(' expresion ')'
    | '(' expresion ')'
    | NUMERO
    ;

NUMERO: [0-9]+ ;

ESPACIOS: [ \t\r\n]+ -> skip;
