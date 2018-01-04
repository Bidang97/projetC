#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define true 1

#define prl { printf("\n"); }
#define NUL 0
#define BOOL 1
#define INT 2
#define FLOAT 3
#define REF 4
#define NAME 5
#define STRING 6
#define STREAM 7
#define ARRAY 8



typedef struct pdf_object_t pdf_object_t;
void pdf_object_free(pdf_object_t* o);
void pdf_fprint_object(FILE* fd, pdf_object_t* o);
typedef union attribute attribute;

union attribute {
  int i;
  float f;
  bool b;
  unsigned int id;
  char *n;
  char *s;
  char *array [10];
 
};

struct pdf_object_t {
    size_t t;
    int objectType; //0:NULL, 1: BOOL, 2: INT..
    attribute *attribute;
  };

  pdf_object_t* pdf_null(pdf_object_t* o){
    if (o != NULL) {
      pdf_object_free(o);
    }
    o = (pdf_object_t*)malloc(sizeof(pdf_object_t)) ;
    o->attribute = (attribute*)malloc(sizeof(attribute));
    o->objectType=NUL;
    return o;
  }

  pdf_object_t* pdf_bool(pdf_object_t* o, bool b){
    if (o == NULL) {
      o = (pdf_object_t*)malloc(sizeof(pdf_object_t)) ;
      o->attribute = (attribute*)malloc(sizeof(attribute));
    } else {
      pdf_object_free(o);
      o = (pdf_object_t*)malloc(sizeof(pdf_object_t)) ;
      o->attribute = (attribute*)malloc(sizeof(attribute));
    }
    o->objectType=BOOL;
    o->attribute->b = b;
    return o;
  }

  pdf_object_t* pdf_int(pdf_object_t* o, int i){
    if (o == NULL) {
      o = (pdf_object_t*)malloc(sizeof(pdf_object_t)) ;
      o->attribute = (attribute*)malloc(sizeof(attribute));
    } else {
      pdf_object_free(o);
      o = (pdf_object_t*)malloc(sizeof(pdf_object_t)) ;
      o->attribute = (attribute*)malloc(sizeof(attribute));
    }
    o->objectType=INT;
    o->attribute->i = i;
    return o;
  }

  pdf_object_t* pdf_real(pdf_object_t* o, float f){
    if (o == NULL) {
      o = (pdf_object_t*)malloc(sizeof(pdf_object_t)) ;
      o->attribute = (attribute*)malloc(sizeof(attribute));

    } else {
      pdf_object_free(o);
      o = (pdf_object_t*)malloc(sizeof(pdf_object_t)) ;
      o->attribute = (attribute*)malloc(sizeof(attribute));
    }
    o->objectType=FLOAT;
    o->attribute->f = f;
    return o;
  }

  pdf_object_t* pdf_reference(pdf_object_t* o, unsigned int id) {
    if (o == NULL) {
      o = (pdf_object_t*)malloc(sizeof(pdf_object_t)) ;
      o->attribute = (attribute*)malloc(sizeof(attribute));

    } else {
      pdf_object_free(o);
      o = (pdf_object_t*)malloc(sizeof(pdf_object_t)) ;
      o->attribute = (attribute*)malloc(sizeof(attribute));
    }
    o->objectType=REF;
    o->attribute->id = id+1;
    return o;
  }

  pdf_object_t* pdf_name(pdf_object_t* o, const char* n) {
    if (o == NULL) {
      o = (pdf_object_t*)malloc(sizeof(pdf_object_t)) ;
      o->attribute = (attribute*)malloc(sizeof(attribute));
      o->attribute->n = malloc(sizeof(strlen(n)+1));
    } else {
      pdf_object_free(o);
      o = (pdf_object_t*)malloc(sizeof(pdf_object_t)) ;
      o->attribute = (attribute*)malloc(sizeof(attribute));
      o->attribute->n = malloc(sizeof(strlen(n)+1));
    }
    o->objectType=NAME;
    strcpy (o->attribute->n,n);
    return o;
  }

  pdf_object_t* pdf_string(pdf_object_t* o, const char* s) {
    if (o == NULL) {
      o = (pdf_object_t*)malloc(sizeof(pdf_object_t)) ;
      o->attribute = (attribute*)malloc(sizeof(attribute));
      o->attribute->s = malloc(sizeof(strlen(s)+1));
    } else {
      pdf_object_free(o);
      o = (pdf_object_t*)malloc(sizeof(pdf_object_t)) ;
      o->attribute = (attribute*)malloc(sizeof(attribute));
      o->attribute->s = malloc(sizeof(strlen(s)+1));
    }
    o->objectType=STRING;
    strcpy (o->attribute->s,s);
    return o;
  }

  pdf_object_t* pdf_array(pdf_object_t* o, size_t n) {
   if (o == NULL) {
    o = (pdf_object_t*)malloc(sizeof(pdf_object_t)) ;
    o->attribute = (attribute*)malloc(sizeof(attribute));
    
  } else {
    pdf_object_free(o);
    o = (pdf_object_t*)malloc(sizeof(pdf_object_t)) ;
    o->attribute = (attribute*)malloc(sizeof(attribute));
    
  }
  o->objectType=ARRAY;
  o->t = n;
  //char *array [n];
  for (int i = 0; i < n; i++) {
    //*(array+1) = NULL;
    o->attribute->array[i] = NULL;
  }
  return o;
}
pdf_object_t* pdf_array_get(pdf_object_t* a, size_t i)
{
  if (o == NULL) {
    o = (pdf_object_t*)malloc(sizeof(pdf_object_t)) ;
    o->attribute = (attribute*)malloc(sizeof(attribute));
    
  } else {
    pdf_object_free(o);
    o = (pdf_object_t*)malloc(sizeof(pdf_object_t)) ;
    o->attribute = (attribute*)malloc(sizeof(attribute));
    
  }
  return o->attribute->array[i];

}

void pdf_fprint_object(FILE* fd, pdf_object_t* o) {
  if(o == NULL) {printf("Printed object is NULL."); return;}
  else {
    switch (o->objectType) {
      case NUL:
      fprintf(fd,"null");
      return;
      case BOOL:
      fprintf(fd,"%s", o->attribute->b ? "true" : "false");
      return;
      case INT:
      fprintf(fd,"%d", o->attribute->i);
      return;
      case FLOAT:
      fprintf(fd,"%.4f", o->attribute->f);
      return;
      case REF:
      fprintf(fd,"%d 0 R", o->attribute->id);
      return;
      case NAME:
      fprintf(fd,"/%s", o->attribute->n);
      return;
      case STRING:
      fprintf(fd,"(%s)", o->attribute->s);
      return;
      case ARRAY:
      fprintf(fd, "[");
      for(int i = 0; i<o->t; i++){
        fprintf(fd, " null ");
      }
      fprintf(fd, "]");
      return;
      default:
      break;
    }


  }
}
void pdf_object_free(pdf_object_t* o)
{
    //    free(o->attribute);
  free(o);
}