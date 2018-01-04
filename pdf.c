
#include "pdf.h"
#define prl {printf ("\n"); }

int main ( )  {
    pdf_object_t * o = NULL;
    o = pdf_null ( o ) ;  printf ( "%p: " , o ) ; pdf_fprint_object ( stdout , o ) ; prl ;
    o = pdf_bool(o, true ); printf( "%p: ", o); pdf_fprint_object(stdout, o); prl;
    o = pdf_bool ( o , false ) ;  printf ( "%p: " , o ) ; pdf_fprint_object ( stdout , o ) ; prl ;
    o = pdf_int ( o , 123 ) ;  printf ( "%p: " , o ) ; pdf_fprint_object ( stdout , o) ; prl ;
    o = pdf_real(o, 123.456); printf("%p: ", o); pdf_fprint_object(stdout, o); prl;
    o = pdf_name(o, "Root"); printf("%p: ", o); pdf_fprint_object(stdout, o); prl;
 	o = pdf_string(o, "Helloworld !!!!"); printf("%p: ", o); pdf_fprint_object(stdout, o); prl;  
 	o = pdf_reference(o, 123); printf("%p: ", o); pdf_fprint_object(stdout, o); prl;
 	o = pdf_array(o, 3); printf("%p: ", o); pdf_fprint_object(stdout, o); prl;
    return 0 ;
}

