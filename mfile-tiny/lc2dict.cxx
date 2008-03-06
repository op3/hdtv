//
// File generated by rootcint at Wed Mar  5 20:56:58 2008

// Do NOT change. Changes will be lost next time file is generated
//

#include "RConfig.h"
#if !defined(R__ACCESS_IN_SYMBOL)
//Break the privacy of classes -- Disabled for the moment
#define private public
#define protected public
#endif

// Since CINT ignores the std namespace, we need to do so in this file.
namespace std {} using namespace std;
#include "lc2dict.h"

#include "TClass.h"
#include "TBuffer.h"
#include "TMemberInspector.h"
#include "TError.h"

#ifndef G__ROOT
#define G__ROOT
#endif

#include "RtypesImp.h"
#include "TIsAProxy.h"

// START OF SHADOWS

namespace ROOT {
   namespace Shadow {
   } // of namespace Shadow
} // of namespace ROOT
// END OF SHADOWS

namespace ROOT {
   void LC2Reader_ShowMembers(void *obj, TMemberInspector &R__insp, char *R__parent);
   static void LC2Reader_Dictionary();
   static void *new_LC2Reader(void *p = 0);
   static void *newArray_LC2Reader(Long_t size, void *p);
   static void delete_LC2Reader(void *p);
   static void deleteArray_LC2Reader(void *p);
   static void destruct_LC2Reader(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::LC2Reader*)
   {
      ::LC2Reader *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::LC2Reader),0);
      static ::ROOT::TGenericClassInfo 
         instance("LC2Reader", "LC2Reader.h", 12,
                  typeid(::LC2Reader), DefineBehavior(ptr, ptr),
                  0, &LC2Reader_Dictionary, isa_proxy, 0,
                  sizeof(::LC2Reader) );
      instance.SetNew(&new_LC2Reader);
      instance.SetNewArray(&newArray_LC2Reader);
      instance.SetDelete(&delete_LC2Reader);
      instance.SetDeleteArray(&deleteArray_LC2Reader);
      instance.SetDestructor(&destruct_LC2Reader);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::LC2Reader*)
   {
      return GenerateInitInstanceLocal((::LC2Reader*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::LC2Reader*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static void LC2Reader_Dictionary() {
      ::ROOT::GenerateInitInstanceLocal((const ::LC2Reader*)0x0)->GetClass();
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_LC2Reader(void *p) {
      return  p ? ::new((::ROOT::TOperatorNewHelper*)p) ::LC2Reader : new ::LC2Reader;
   }
   static void *newArray_LC2Reader(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::TOperatorNewHelper*)p) ::LC2Reader[nElements] : new ::LC2Reader[nElements];
   }
   // Wrapper around operator delete
   static void delete_LC2Reader(void *p) {
      delete ((::LC2Reader*)p);
   }
   static void deleteArray_LC2Reader(void *p) {
      delete [] ((::LC2Reader*)p);
   }
   static void destruct_LC2Reader(void *p) {
      typedef ::LC2Reader current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::LC2Reader

/********************************************************
* lc2dict.cxx
* CAUTION: DON'T CHANGE THIS FILE. THIS FILE IS AUTOMATICALLY GENERATED
*          FROM HEADER FILES LISTED IN G__setup_cpp_environmentXXX().
*          CHANGE THOSE HEADER FILES AND REGENERATE THIS FILE.
********************************************************/

#ifdef G__MEMTEST
#undef malloc
#undef free
#endif

extern "C" void G__cpp_reset_tagtablelc2dict();

extern "C" void G__set_cpp_environmentlc2dict() {
  G__add_compiledheader("TObject.h");
  G__add_compiledheader("TMemberInspector.h");
  G__add_compiledheader("LC2Reader.h");
  G__cpp_reset_tagtablelc2dict();
}
#include <new>
extern "C" int G__cpp_dllrevlc2dict() { return(30051515); }

/*********************************************************
* Member function Interface Method
*********************************************************/

/* LC2Reader */
static int G__lc2dict_138_0_1(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
   LC2Reader* p = NULL;
   long gvp = G__getgvp();
   int n = G__getaryconstruct();
   if (n) {
     if ((gvp == G__PVOID) || (gvp == 0)) {
       p = new LC2Reader[n];
     } else {
       p = new((void*) gvp) LC2Reader[n];
     }
   } else {
     if ((gvp == G__PVOID) || (gvp == 0)) {
       p = new LC2Reader;
     } else {
       p = new((void*) gvp) LC2Reader;
     }
   }
   result7->obj.i = (long) p;
   result7->ref = (long) p;
   result7->type = 'u';
   result7->tagnum = G__get_linked_tagnum(&G__lc2dictLN_LC2Reader);
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__lc2dict_138_0_2(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 105, (long) ((LC2Reader*) G__getstructoffset())->Open((char*) G__int(libp->para[0])));
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__lc2dict_138_0_3(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 105, (long) ((LC2Reader*) G__getstructoffset())->Close());
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__lc2dict_138_0_4(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 105, (long) ((LC2Reader*) G__getstructoffset())->Probe());
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__lc2dict_138_0_5(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 105, (long) ((LC2Reader*) G__getstructoffset())->GetNumBins());
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__lc2dict_138_0_6(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 105, (long) ((LC2Reader*) G__getstructoffset())->GetNumLines());
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__lc2dict_138_0_7(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
   switch (libp->paran) {
   case 2:
      G__letint(result7, 105, (long) ((LC2Reader*) G__getstructoffset())->Fill((TH1*) G__int(libp->para[0]), (int) G__int(libp->para[1])));
      break;
   case 1:
      G__letint(result7, 105, (long) ((LC2Reader*) G__getstructoffset())->Fill((TH1*) G__int(libp->para[0])));
      break;
   }
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__lc2dict_138_0_8(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 105, (long) ((LC2Reader*) G__getstructoffset())->FillMatrix((TH2*) G__int(libp->para[0])));
   return(1 || funcname || hash || result7 || libp) ;
}

// automatic copy constructor
static int G__lc2dict_138_0_10(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)

{
   LC2Reader* p;
   void* tmp = (void*) G__int(libp->para[0]);
   p = new LC2Reader(*(LC2Reader*) tmp);
   result7->obj.i = (long) p;
   result7->ref = (long) p;
   result7->type = 'u';
   result7->tagnum = G__get_linked_tagnum(&G__lc2dictLN_LC2Reader);
   return(1 || funcname || hash || result7 || libp) ;
}

// automatic destructor
typedef LC2Reader G__TLC2Reader;
static int G__lc2dict_138_0_11(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
   long gvp = G__getgvp();
   long soff = G__getstructoffset();
   int n = G__getaryconstruct();
   //
   //has_a_delete: 0
   //has_own_delete1arg: 0
   //has_own_delete2arg: 0
   //
   if (!soff) {
     return(1);
   }
   if (n) {
     if (gvp == G__PVOID) {
       delete[] (LC2Reader*) soff;
     } else {
       G__setgvp(G__PVOID);
       for (int i = n - 1; i >= 0; --i) {
         ((LC2Reader*) (soff+(sizeof(LC2Reader)*i)))->~G__TLC2Reader();
       }
       G__setgvp(gvp);
     }
   } else {
     if (gvp == G__PVOID) {
       delete (LC2Reader*) soff;
     } else {
       G__setgvp(G__PVOID);
       ((LC2Reader*) (soff))->~G__TLC2Reader();
       G__setgvp(gvp);
     }
   }
   G__setnull(result7);
   return(1 || funcname || hash || result7 || libp) ;
}

// automatic assignment operator
static int G__lc2dict_138_0_12(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
   LC2Reader* dest = (LC2Reader*) G__getstructoffset();
   *dest = *(LC2Reader*) libp->para[0].ref;
   const LC2Reader& obj = *dest;
   result7->ref = (long) (&obj);
   result7->obj.i = (long) (&obj);
   return(1 || funcname || hash || result7 || libp) ;
}


/* Setting up global function */

/*********************************************************
* Member function Stub
*********************************************************/

/* LC2Reader */

/*********************************************************
* Global function Stub
*********************************************************/

/*********************************************************
* Get size of pointer to member function
*********************************************************/
class G__Sizep2memfunclc2dict {
 public:
  G__Sizep2memfunclc2dict(): p(&G__Sizep2memfunclc2dict::sizep2memfunc) {}
    size_t sizep2memfunc() { return(sizeof(p)); }
  private:
    size_t (G__Sizep2memfunclc2dict::*p)();
};

size_t G__get_sizep2memfunclc2dict()
{
  G__Sizep2memfunclc2dict a;
  G__setsizep2memfunc((int)a.sizep2memfunc());
  return((size_t)a.sizep2memfunc());
}


/*********************************************************
* virtual base class offset calculation interface
*********************************************************/

   /* Setting up class inheritance */

/*********************************************************
* Inheritance information setup/
*********************************************************/
extern "C" void G__cpp_setup_inheritancelc2dict() {

   /* Setting up class inheritance */
}

/*********************************************************
* typedef information setup/
*********************************************************/
extern "C" void G__cpp_setup_typetablelc2dict() {

   /* Setting up typedef entry */
   G__search_typename2("TVectorT<Float_t>",117,G__get_linked_tagnum(&G__lc2dictLN_TVectorTlEfloatgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("TVectorT<Double_t>",117,G__get_linked_tagnum(&G__lc2dictLN_TVectorTlEdoublegR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("TMatrixTBase<Float_t>",117,G__get_linked_tagnum(&G__lc2dictLN_TMatrixTBaselEfloatgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("TMatrixTBase<Double_t>",117,G__get_linked_tagnum(&G__lc2dictLN_TMatrixTBaselEdoublegR),0,-1);
   G__setnewtype(-1,NULL,0);
}

/*********************************************************
* Data Member information setup/
*********************************************************/

   /* Setting up class,struct,union tag member variable */

   /* LC2Reader */
static void G__setup_memvarLC2Reader(void) {
   G__tag_memvar_setup(G__get_linked_tagnum(&G__lc2dictLN_LC2Reader));
   { LC2Reader *p; p=(LC2Reader*)0x1000; if (p) { }
   G__memvar_setup((void*)0,105,0,0,-1,-1,-1,4,"handle=",0,(char*)NULL);
   G__memvar_setup((void*)0,85,0,0,G__get_linked_tagnum(&G__lc2dictLN_lc_header),G__defined_typename("lc_header"),-1,4,"header=",0,(char*)NULL);
   G__memvar_setup((void*)0,85,0,0,G__get_linked_tagnum(&G__lc2dictLN_lc_poslen),G__defined_typename("lc_poslen"),-1,4,"poslen_tbl=",0,(char*)NULL);
   }
   G__tag_memvar_reset();
}

extern "C" void G__cpp_setup_memvarlc2dict() {
}
/***********************************************************
************************************************************
************************************************************
************************************************************
************************************************************
************************************************************
************************************************************
***********************************************************/

/*********************************************************
* Member function information setup for each class
*********************************************************/
static void G__setup_memfuncLC2Reader(void) {
   /* LC2Reader */
   G__tag_memfunc_setup(G__get_linked_tagnum(&G__lc2dictLN_LC2Reader));
   G__memfunc_setup("LC2Reader",788,G__lc2dict_138_0_1, 105, G__get_linked_tagnum(&G__lc2dictLN_LC2Reader), -1, 0, 0, 1, 1, 0, "", (char*)NULL, (void*) NULL, 0);
   G__memfunc_setup("Open",402,G__lc2dict_138_0_2, 105, -1, -1, 0, 1, 1, 1, 0, "C - - 0 - filename", (char*)NULL, (void*) NULL, 0);
   G__memfunc_setup("Close",502,G__lc2dict_138_0_3, 105, -1, -1, 0, 0, 1, 1, 0, "", (char*)NULL, (void*) NULL, 0);
   G__memfunc_setup("Probe",504,G__lc2dict_138_0_4, 105, -1, -1, 0, 0, 1, 1, 0, "", (char*)NULL, (void*) NULL, 0);
   G__memfunc_setup("GetNumBins",988,G__lc2dict_138_0_5, 105, -1, -1, 0, 0, 1, 1, 0, "", (char*)NULL, (void*) NULL, 0);
   G__memfunc_setup("GetNumLines",1099,G__lc2dict_138_0_6, 105, -1, -1, 0, 0, 1, 1, 0, "", (char*)NULL, (void*) NULL, 0);
   G__memfunc_setup("Fill",391,G__lc2dict_138_0_7, 105, -1, -1, 0, 2, 1, 1, 0, 
"U 'TH1' - 0 - hist i - - 0 '0' idx", (char*)NULL, (void*) NULL, 0);
   G__memfunc_setup("FillMatrix",1020,G__lc2dict_138_0_8, 105, -1, -1, 0, 1, 1, 1, 0, "U 'TH2' - 0 - hist", (char*)NULL, (void*) NULL, 0);
   G__memfunc_setup("EnsureHeader",1211,(G__InterfaceMethod) NULL, 105, -1, -1, 0, 0, 1, 4, 0, "", (char*)NULL, (void*) NULL, 0);
   // automatic copy constructor
   G__memfunc_setup("LC2Reader", 788, G__lc2dict_138_0_10, (int) ('i'), G__get_linked_tagnum(&G__lc2dictLN_LC2Reader), -1, 0, 1, 1, 1, 0, "u 'LC2Reader' - 11 - -", (char*) NULL, (void*) NULL, 0);
   // automatic destructor
   G__memfunc_setup("~LC2Reader", 914, G__lc2dict_138_0_11, (int) ('y'), -1, -1, 0, 0, 1, 1, 0, "", (char*) NULL, (void*) NULL, 0);
   // automatic assignment operator
   G__memfunc_setup("operator=", 937, G__lc2dict_138_0_12, (int) ('u'), G__get_linked_tagnum(&G__lc2dictLN_LC2Reader), -1, 1, 1, 1, 1, 0, "u 'LC2Reader' - 11 - -", (char*) NULL, (void*) NULL, 0);
   G__tag_memfunc_reset();
}


/*********************************************************
* Member function information setup
*********************************************************/
extern "C" void G__cpp_setup_memfunclc2dict() {
}

/*********************************************************
* Global variable information setup for each class
*********************************************************/
static void G__cpp_setup_global0() {

   /* Setting up global variables */
   G__resetplocal();

}

static void G__cpp_setup_global1() {
}

static void G__cpp_setup_global2() {

   G__resetglobalenv();
}
extern "C" void G__cpp_setup_globallc2dict() {
  G__cpp_setup_global0();
  G__cpp_setup_global1();
  G__cpp_setup_global2();
}

/*********************************************************
* Global function information setup for each class
*********************************************************/
static void G__cpp_setup_func0() {
   G__lastifuncposition();

}

static void G__cpp_setup_func1() {
}

static void G__cpp_setup_func2() {
}

static void G__cpp_setup_func3() {
}

static void G__cpp_setup_func4() {

   G__resetifuncposition();
}

extern "C" void G__cpp_setup_funclc2dict() {
  G__cpp_setup_func0();
  G__cpp_setup_func1();
  G__cpp_setup_func2();
  G__cpp_setup_func3();
  G__cpp_setup_func4();
}

/*********************************************************
* Class,struct,union,enum tag information setup
*********************************************************/
/* Setup class/struct taginfo */
G__linked_taginfo G__lc2dictLN_TVectorTlEfloatgR = { "TVectorT<float>" , 99 , -1 };
G__linked_taginfo G__lc2dictLN_TVectorTlEdoublegR = { "TVectorT<double>" , 99 , -1 };
G__linked_taginfo G__lc2dictLN_TH1 = { "TH1" , 99 , -1 };
G__linked_taginfo G__lc2dictLN_TMatrixTBaselEfloatgR = { "TMatrixTBase<float>" , 99 , -1 };
G__linked_taginfo G__lc2dictLN_TMatrixTBaselEdoublegR = { "TMatrixTBase<double>" , 99 , -1 };
G__linked_taginfo G__lc2dictLN_TH2 = { "TH2" , 99 , -1 };
G__linked_taginfo G__lc2dictLN_lc_header = { "lc_header" , 115 , -1 };
G__linked_taginfo G__lc2dictLN_lc_poslen = { "lc_poslen" , 115 , -1 };
G__linked_taginfo G__lc2dictLN_LC2Reader = { "LC2Reader" , 99 , -1 };

/* Reset class/struct taginfo */
extern "C" void G__cpp_reset_tagtablelc2dict() {
  G__lc2dictLN_TVectorTlEfloatgR.tagnum = -1 ;
  G__lc2dictLN_TVectorTlEdoublegR.tagnum = -1 ;
  G__lc2dictLN_TH1.tagnum = -1 ;
  G__lc2dictLN_TMatrixTBaselEfloatgR.tagnum = -1 ;
  G__lc2dictLN_TMatrixTBaselEdoublegR.tagnum = -1 ;
  G__lc2dictLN_TH2.tagnum = -1 ;
  G__lc2dictLN_lc_header.tagnum = -1 ;
  G__lc2dictLN_lc_poslen.tagnum = -1 ;
  G__lc2dictLN_LC2Reader.tagnum = -1 ;
}


extern "C" void G__cpp_setup_tagtablelc2dict() {

   /* Setting up class,struct,union tag entry */
   G__get_linked_tagnum_fwd(&G__lc2dictLN_TVectorTlEfloatgR);
   G__get_linked_tagnum_fwd(&G__lc2dictLN_TVectorTlEdoublegR);
   G__get_linked_tagnum_fwd(&G__lc2dictLN_TH1);
   G__get_linked_tagnum_fwd(&G__lc2dictLN_TMatrixTBaselEfloatgR);
   G__get_linked_tagnum_fwd(&G__lc2dictLN_TMatrixTBaselEdoublegR);
   G__get_linked_tagnum_fwd(&G__lc2dictLN_TH2);
   G__get_linked_tagnum_fwd(&G__lc2dictLN_lc_header);
   G__get_linked_tagnum_fwd(&G__lc2dictLN_lc_poslen);
   G__tagtable_setup(G__get_linked_tagnum(&G__lc2dictLN_LC2Reader),sizeof(LC2Reader),-1,1280,(char*)NULL,G__setup_memvarLC2Reader,G__setup_memfuncLC2Reader);
}
extern "C" void G__cpp_setuplc2dict(void) {
  G__check_setup_version(30051515,"G__cpp_setuplc2dict()");
  G__set_cpp_environmentlc2dict();
  G__cpp_setup_tagtablelc2dict();

  G__cpp_setup_inheritancelc2dict();

  G__cpp_setup_typetablelc2dict();

  G__cpp_setup_memvarlc2dict();

  G__cpp_setup_memfunclc2dict();
  G__cpp_setup_globallc2dict();
  G__cpp_setup_funclc2dict();

   if(0==G__getsizep2memfunc()) G__get_sizep2memfunclc2dict();
  return;
}
class G__cpp_setup_initlc2dict {
  public:
    G__cpp_setup_initlc2dict() { G__add_setup_func("lc2dict",(G__incsetup)(&G__cpp_setuplc2dict)); G__call_setup_funcs(); }
   ~G__cpp_setup_initlc2dict() { G__remove_setup_func("lc2dict"); }
};
G__cpp_setup_initlc2dict G__cpp_setup_initializerlc2dict;

