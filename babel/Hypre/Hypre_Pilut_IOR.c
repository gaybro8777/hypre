/*
 * File:          Hypre_Pilut_IOR.c
 * Symbol:        Hypre.Pilut-v0.1.5
 * Symbol Type:   class
 * Babel Version: 0.6.3
 * SIDL Created:  20020522 13:59:35 PDT
 * Generated:     20020522 13:59:38 PDT
 * Description:   Intermediate Object Representation for Hypre.Pilut
 * 
 * WARNING: Automatically generated; changes will be lost
 * 
 */

#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include "Hypre_Pilut_IOR.h"

#ifndef NULL
#define NULL 0
#endif

/*
 * Static variables for managing EPV initialization.
 */

static int s_method_initialized = 0;
static int s_remote_initialized = 0;

static struct Hypre_Pilut__epv s_new__hypre_pilut;
static struct Hypre_Pilut__epv s_rem__hypre_pilut;

static struct Hypre_Operator__epv s_new__hypre_operator;
static struct Hypre_Operator__epv s_rem__hypre_operator;

static struct Hypre_Solver__epv s_new__hypre_solver;
static struct Hypre_Solver__epv s_rem__hypre_solver;

static struct SIDL_BaseClass__epv  s_new__sidl_baseclass;
static struct SIDL_BaseClass__epv* s_old__sidl_baseclass;
static struct SIDL_BaseClass__epv  s_rem__sidl_baseclass;

static struct SIDL_BaseInterface__epv  s_new__sidl_baseinterface;
static struct SIDL_BaseInterface__epv* s_old__sidl_baseinterface;
static struct SIDL_BaseInterface__epv  s_rem__sidl_baseinterface;

/*
 * Declare EPV routines defined in the skeleton file.
 */

extern void Hypre_Pilut__set_epv(
  struct Hypre_Pilut__epv* epv);

/*
 * CAST: dynamic type casting support.
 */

static void* Hypre_Pilut__cast(
  struct Hypre_Pilut__object* self,
  const char* name)
{
  void* cast = NULL;

  struct Hypre_Pilut__object*    s0 = self;
  struct SIDL_BaseClass__object* s1 = &s0->d_sidl_baseclass;

  if (!strcmp(name, "Hypre.Pilut")) {
    cast = (void*) s0;
  } else if (!strcmp(name, "Hypre.Operator")) {
    cast = (void*) &s0->d_hypre_operator;
  } else if (!strcmp(name, "Hypre.Solver")) {
    cast = (void*) &s0->d_hypre_solver;
  } else if (!strcmp(name, "SIDL.BaseClass")) {
    cast = (void*) s1;
  } else if (!strcmp(name, "SIDL.BaseInterface")) {
    cast = (void*) &s1->d_sidl_baseinterface;
  }

  return cast;
}

/*
 * DELETE: call destructor and free object memory.
 */

static void Hypre_Pilut__delete(
  struct Hypre_Pilut__object* self)
{
  Hypre_Pilut__fini(self);
  memset((void*)self, 0, sizeof(struct Hypre_Pilut__object));
  free((void*) self);
}

/*
 * EPV: create method entry point vector (EPV) structure.
 */

static void Hypre_Pilut__init_epv(
  struct Hypre_Pilut__object* self)
{
  struct Hypre_Pilut__object*    s0 = self;
  struct SIDL_BaseClass__object* s1 = &s0->d_sidl_baseclass;

  struct Hypre_Pilut__epv*        epv = &s_new__hypre_pilut;
  struct Hypre_Operator__epv*     e0  = &s_new__hypre_operator;
  struct Hypre_Solver__epv*       e1  = &s_new__hypre_solver;
  struct SIDL_BaseClass__epv*     e2  = &s_new__sidl_baseclass;
  struct SIDL_BaseInterface__epv* e3  = &s_new__sidl_baseinterface;

  s_old__sidl_baseinterface = s1->d_sidl_baseinterface.d_epv;
  s_old__sidl_baseclass     = s1->d_epv;

  epv->f__cast                   = Hypre_Pilut__cast;
  epv->f__delete                 = Hypre_Pilut__delete;
  epv->f__ctor                   = NULL;
  epv->f__dtor                   = NULL;
  epv->f_Apply                   = NULL;
  epv->f_GetResidual             = NULL;
  epv->f_SetCommunicator         = NULL;
  epv->f_SetDoubleArrayParameter = NULL;
  epv->f_SetDoubleParameter      = NULL;
  epv->f_SetIntArrayParameter    = NULL;
  epv->f_SetIntParameter         = NULL;
  epv->f_SetLogging              = NULL;
  epv->f_SetOperator             = NULL;
  epv->f_SetPrintLevel           = NULL;
  epv->f_SetStringParameter      = NULL;
  epv->f_Setup                   = NULL;
  epv->f_addReference            = (void (*)(struct Hypre_Pilut__object*)) 
    s1->d_epv->f_addReference;
  epv->f_deleteReference         = (void (*)(struct Hypre_Pilut__object*)) 
    s1->d_epv->f_deleteReference;
  epv->f_isInstanceOf            = (SIDL_bool (*)(struct Hypre_Pilut__object*,
    const char*)) s1->d_epv->f_isInstanceOf;
  epv->f_isSame                  = (SIDL_bool (*)(struct Hypre_Pilut__object*,
    struct SIDL_BaseInterface__object*)) s1->d_epv->f_isSame;
  epv->f_queryInterface          = (struct SIDL_BaseInterface__object* 
    (*)(struct Hypre_Pilut__object*,const char*)) s1->d_epv->f_queryInterface;

  Hypre_Pilut__set_epv(epv);

  e0->f__cast                   = (void* (*)(void*,const char*)) epv->f__cast;
  e0->f__delete                 = (void (*)(void*)) epv->f__delete;
  e0->f_Apply                   = (int32_t (*)(void*,
    struct Hypre_Vector__object*,struct Hypre_Vector__object**)) epv->f_Apply;
  e0->f_SetCommunicator         = (int32_t (*)(void*,
    void*)) epv->f_SetCommunicator;
  e0->f_SetDoubleArrayParameter = (int32_t (*)(void*,const char*,
    struct SIDL_double__array*)) epv->f_SetDoubleArrayParameter;
  e0->f_SetDoubleParameter      = (int32_t (*)(void*,const char*,
    double)) epv->f_SetDoubleParameter;
  e0->f_SetIntArrayParameter    = (int32_t (*)(void*,const char*,
    struct SIDL_int__array*)) epv->f_SetIntArrayParameter;
  e0->f_SetIntParameter         = (int32_t (*)(void*,const char*,
    int32_t)) epv->f_SetIntParameter;
  e0->f_SetStringParameter      = (int32_t (*)(void*,const char*,
    const char*)) epv->f_SetStringParameter;
  e0->f_Setup                   = (int32_t (*)(void*)) epv->f_Setup;
  e0->f_addReference            = (void (*)(void*)) epv->f_addReference;
  e0->f_deleteReference         = (void (*)(void*)) epv->f_deleteReference;
  e0->f_isInstanceOf            = (SIDL_bool (*)(void*,
    const char*)) epv->f_isInstanceOf;
  e0->f_isSame                  = (SIDL_bool (*)(void*,
    struct SIDL_BaseInterface__object*)) epv->f_isSame;
  e0->f_queryInterface          = (struct SIDL_BaseInterface__object* (*)(void*,
    const char*)) epv->f_queryInterface;

  e1->f__cast                   = (void* (*)(void*,const char*)) epv->f__cast;
  e1->f__delete                 = (void (*)(void*)) epv->f__delete;
  e1->f_Apply                   = (int32_t (*)(void*,
    struct Hypre_Vector__object*,struct Hypre_Vector__object**)) epv->f_Apply;
  e1->f_GetResidual             = (int32_t (*)(void*,
    struct Hypre_Vector__object**)) epv->f_GetResidual;
  e1->f_SetCommunicator         = (int32_t (*)(void*,
    void*)) epv->f_SetCommunicator;
  e1->f_SetDoubleArrayParameter = (int32_t (*)(void*,const char*,
    struct SIDL_double__array*)) epv->f_SetDoubleArrayParameter;
  e1->f_SetDoubleParameter      = (int32_t (*)(void*,const char*,
    double)) epv->f_SetDoubleParameter;
  e1->f_SetIntArrayParameter    = (int32_t (*)(void*,const char*,
    struct SIDL_int__array*)) epv->f_SetIntArrayParameter;
  e1->f_SetIntParameter         = (int32_t (*)(void*,const char*,
    int32_t)) epv->f_SetIntParameter;
  e1->f_SetLogging              = (int32_t (*)(void*,
    int32_t)) epv->f_SetLogging;
  e1->f_SetOperator             = (int32_t (*)(void*,
    struct Hypre_Operator__object*)) epv->f_SetOperator;
  e1->f_SetPrintLevel           = (int32_t (*)(void*,
    int32_t)) epv->f_SetPrintLevel;
  e1->f_SetStringParameter      = (int32_t (*)(void*,const char*,
    const char*)) epv->f_SetStringParameter;
  e1->f_Setup                   = (int32_t (*)(void*)) epv->f_Setup;
  e1->f_addReference            = (void (*)(void*)) epv->f_addReference;
  e1->f_deleteReference         = (void (*)(void*)) epv->f_deleteReference;
  e1->f_isInstanceOf            = (SIDL_bool (*)(void*,
    const char*)) epv->f_isInstanceOf;
  e1->f_isSame                  = (SIDL_bool (*)(void*,
    struct SIDL_BaseInterface__object*)) epv->f_isSame;
  e1->f_queryInterface          = (struct SIDL_BaseInterface__object* (*)(void*,
    const char*)) epv->f_queryInterface;

  e2->f__cast           = (void* (*)(struct SIDL_BaseClass__object*,
    const char*)) epv->f__cast;
  e2->f__delete         = (void (*)(struct SIDL_BaseClass__object*)) 
    epv->f__delete;
  e2->f_addReference    = (void (*)(struct SIDL_BaseClass__object*)) 
    epv->f_addReference;
  e2->f_deleteReference = (void (*)(struct SIDL_BaseClass__object*)) 
    epv->f_deleteReference;
  e2->f_isInstanceOf    = (SIDL_bool (*)(struct SIDL_BaseClass__object*,
    const char*)) epv->f_isInstanceOf;
  e2->f_isSame          = (SIDL_bool (*)(struct SIDL_BaseClass__object*,
    struct SIDL_BaseInterface__object*)) epv->f_isSame;
  e2->f_queryInterface  = (struct SIDL_BaseInterface__object* (*)(struct 
    SIDL_BaseClass__object*,const char*)) epv->f_queryInterface;

  e3->f__cast           = (void* (*)(void*,const char*)) epv->f__cast;
  e3->f__delete         = (void (*)(void*)) epv->f__delete;
  e3->f_addReference    = (void (*)(void*)) epv->f_addReference;
  e3->f_deleteReference = (void (*)(void*)) epv->f_deleteReference;
  e3->f_isInstanceOf    = (SIDL_bool (*)(void*,
    const char*)) epv->f_isInstanceOf;
  e3->f_isSame          = (SIDL_bool (*)(void*,
    struct SIDL_BaseInterface__object*)) epv->f_isSame;
  e3->f_queryInterface  = (struct SIDL_BaseInterface__object* (*)(void*,
    const char*)) epv->f_queryInterface;

  s_method_initialized = 1;
}

/*
 * NEW: allocate object and initialize it.
 */

struct Hypre_Pilut__object*
Hypre_Pilut__new(void)
{
  struct Hypre_Pilut__object* self =
    (struct Hypre_Pilut__object*) malloc(
      sizeof(struct Hypre_Pilut__object));
  Hypre_Pilut__init(self);
  return self;
}

/*
 * INIT: initialize a new instance of the class object.
 */

void Hypre_Pilut__init(
  struct Hypre_Pilut__object* self)
{
  struct Hypre_Pilut__object*    s0 = self;
  struct SIDL_BaseClass__object* s1 = &s0->d_sidl_baseclass;

  SIDL_BaseClass__init(s1);

  if (!s_method_initialized) {
    Hypre_Pilut__init_epv(s0);
  }

  s1->d_sidl_baseinterface.d_epv = &s_new__sidl_baseinterface;
  s1->d_epv                      = &s_new__sidl_baseclass;

  s0->d_hypre_operator.d_epv = &s_new__hypre_operator;
  s0->d_hypre_solver.d_epv   = &s_new__hypre_solver;
  s0->d_epv                  = &s_new__hypre_pilut;

  s0->d_hypre_operator.d_object = self;

  s0->d_hypre_solver.d_object = self;

  s0->d_data = NULL;

  (*(self->d_epv->f__ctor))(self);
}

/*
 * FINI: deallocate a class instance (destructor).
 */

void Hypre_Pilut__fini(
  struct Hypre_Pilut__object* self)
{
  struct Hypre_Pilut__object*    s0 = self;
  struct SIDL_BaseClass__object* s1 = &s0->d_sidl_baseclass;

  (*(s0->d_epv->f__dtor))(s0);

  s1->d_sidl_baseinterface.d_epv = s_old__sidl_baseinterface;
  s1->d_epv                      = s_old__sidl_baseclass;

  SIDL_BaseClass__fini(s1);
}

/*
 * Define the IOR array structure.
 * Macros to read this are defined in SIDLArray.h
 */

struct Hypre_Pilut__array {
  struct Hypre_Pilut__object** d_firstElement;
  int32_t                      *d_lower;
  int32_t                      *d_upper;
  int32_t                      *d_stride;
  SIDL_bool                    d_borrowed;
  int32_t                      d_dimen;
};

static struct Hypre_Pilut__array*
newArray(int32_t dimen, const int32_t lower[], const int32_t upper[]) {
  static const size_t arraySize = sizeof(struct Hypre_Pilut__array)
    + (sizeof(int32_t) - (sizeof(struct Hypre_Pilut__array)
    % sizeof(int32_t))) % sizeof(int32_t);
  struct Hypre_Pilut__array *result =
    (struct Hypre_Pilut__array *)
    malloc(arraySize + 3 * sizeof(int32_t) * dimen);
  result->d_dimen = dimen;
  result->d_borrowed = 0;
  result->d_lower = (int32_t *)((char *)result + arraySize);
  result->d_upper = result->d_lower + dimen;
  result->d_stride = result->d_upper + dimen;
  memcpy(result->d_lower, lower, sizeof(int32_t)*dimen);
  memcpy(result->d_upper, upper, sizeof(int32_t)*dimen);
  return result;
}

/*
 * Create a dense array of the given dimension with specified
 * index bounds.  This array owns and manages its data.
 * All object pointers are initialized to NULL.
 */

struct Hypre_Pilut__array*
Hypre_Pilut__iorarray_create(
  int32_t       dimen,
  const int32_t lower[],
  const int32_t upper[])
{
  int32_t size=1, i;
  struct Hypre_Pilut__array *result = newArray(dimen, lower, upper);
  for(i = 0; i < dimen; ++i) {
    result->d_stride[i] = size;
    size *= (1 + upper[i] - lower[i]);
  }
  size *= sizeof(struct Hypre_Pilut__object*);
  result->d_firstElement = (struct Hypre_Pilut__object**)
    malloc(size);
  memset(result->d_firstElement, 0, size);
  return result;
}

/*
 * Create an array that uses data memory from another source.
 * This initial contents are determined by the data being
 * borrowed.
 */

struct Hypre_Pilut__array*
Hypre_Pilut__iorarray_borrow(
  struct Hypre_Pilut__object** firstElement,
  int32_t                      dimen,
  const int32_t                lower[],
  const int32_t                upper[],
  const int32_t                stride[])
{
  struct Hypre_Pilut__array *result = newArray(dimen, lower, upper);
  memcpy(result->d_stride, stride, sizeof(int32_t)*dimen);
  result->d_firstElement = firstElement;
  result->d_borrowed = 1;
  return result;
}

/*
 * Destroy the given array. Trying to destroy a NULL array is a
 * noop.
 */

void
Hypre_Pilut__iorarray_destroy(
  struct Hypre_Pilut__array* array)
{
  if (array) {
    const int32_t dimen = array->d_dimen;
    if (!(array->d_borrowed)) {
      if (dimen > 0) {
        int32_t size = 1;
        struct Hypre_Pilut__object** start = array->d_firstElement;
        struct Hypre_Pilut__object** end;
        if (dimen > 1) {
          size = array->d_stride[dimen-1];
        }
        size *= (1 + array->d_upper[dimen-1] - array->d_lower[dimen-1]);
        end = start + size;
        while (start < end) {
          if (*start) {
            (*((*start)->d_epv->f_deleteReference))((*start));
            *start = NULL;
          }
          ++start;
        }
      }
      free(array->d_firstElement);
    }
    memset(array, 0, sizeof(struct Hypre_Pilut__array)
      + 3 * dimen * sizeof(int32_t));
    free(array);
  }
}

/*
 * Get an element of a multi-dimensional array. This will use
 * the indices provided up to the actual dimension of the array.
 * The values of excess indices are ignored.
 * 
 * If the return value is non-NULL, the client owns one
 * reference to the object/interface. The client must
 * decrement the reference count when done with the reference.
 */

struct Hypre_Pilut__object*
Hypre_Pilut__iorarray_get(
  const struct Hypre_Pilut__array* array,
  const int32_t                    indices[])
{
  struct Hypre_Pilut__object** result = NULL;
  if (array && (array->d_dimen > 0)) {
    int32_t i;
    result = array->d_firstElement;
    for(i = 0;i < array->d_dimen; ++i) {
      if ((indices[i] >= array->d_lower[i]) &&
        (indices[i] <= array->d_upper[i]))
      {
        result += (array->d_stride[i]*(indices[i] - array->d_lower[i]));
      }
      else {
        result = NULL;
        break;
      }
    }
  }
  if (result) {
    if (*result) {
      (*((*result)->d_epv->f_addReference))((*result));
    }
    return *result;
  }
  else {
    return NULL;
  }
}

/*
 * Set an element of a multi-dimensional array. This will use
 * the indices provided up to the actual dimension of the array.
 * The values of excess indices are ignored.
 * 
 * If the incoming value is non-NULL, this function will increment
 * the reference code of the object/interface. If it is
 * overwriting a non-NULL pointer, the reference count of the
 * object/interface being overwritten will be decremented.
 */

void
Hypre_Pilut__iorarray_set(
  struct Hypre_Pilut__array*  array,
  const int32_t               indices[],
  struct Hypre_Pilut__object* value)
{
  struct Hypre_Pilut__object** result = NULL;
  if (array && (array->d_dimen > 0)) {
    int32_t i;
    result = array->d_firstElement;
    for(i = 0;i < array->d_dimen; ++i) {
      if ((indices[i] >= array->d_lower[i]) &&
        (indices[i] <= array->d_upper[i]))
      {
        result += (array->d_stride[i]*(indices[i] - array->d_lower[i]));
      }
      else {
        result = NULL;
        break;
      }
    }
    if (result) {
      if (value) {
        (*(value->d_epv->f_addReference))(value);
      }
      if (*result) {
        (*((*result)->d_epv->f_deleteReference))((*result));
      }
      *result = value;
    }
  }
}

/*
 * Get an element of a multi-dimensional array. This will use
 * the indices provided up to the actual dimension of the array.
 * The values of excess indices are ignored.
 * 
 * If the return value is non-NULL, the client owns one
 * reference to the object/interface. The client must
 * decrement the reference count when done with the reference.
 */

struct Hypre_Pilut__object*
Hypre_Pilut__iorarray_get4(
  const struct Hypre_Pilut__array* array,
  int32_t                          i1,
  int32_t                          i2,
  int32_t                          i3,
  int32_t                          i4)
{
  struct Hypre_Pilut__object** result = NULL;
  if (array) {
    result = array->d_firstElement;
    switch (array->d_dimen) {
    case 4:
      if ((i4 >= array->d_lower[3]) && (i4 <= array->d_upper[3])) {
        result += (array->d_stride[3]*(i4 - array->d_lower[3]));
      }
      else {
        result = NULL;
        break;
      }
      /* fall through */
    case 3:
      if ((i3 >= array->d_lower[2]) && (i3 <= array->d_upper[2])) {
        result += (array->d_stride[2]*(i3 - array->d_lower[2]));
      }
      else {
        result = NULL;
        break;
      }
      /* fall through */
    case 2:
      if ((i2 >= array->d_lower[1]) && (i2 <= array->d_upper[1])) {
        result += (array->d_stride[1]*(i2 - array->d_lower[1]));
      }
      else {
        result = NULL;
        break;
      }
      /* fall through */
    case 1:
      if ((i1 >= array->d_lower[0]) && (i1 <= array->d_upper[0])) {
        result += (array->d_stride[0]*(i1 - array->d_lower[0]));
      }
      else {
        result = NULL;
        break;
      }
      break;
    default:
      result = NULL;
      break;
    }
  }
  if (result) {
    if (*result) {
      (*((*result)->d_epv->f_addReference))((*result));
    }
    return *result;
  }
  else {
    return NULL;
  }
}

/*
 * Set an element of a multi-dimensional array. This will use
 * the indices provided up to the actual dimension of the array.
 * The values of excess indices are ignored.
 * 
 * If the incoming value is non-NULL, this function will increment
 * the reference code of the object/interface. If it is
 * overwriting a non-NULL pointer, the reference count of the
 * object/interface being overwritten will be decremented.
 */

void
Hypre_Pilut__iorarray_set4(
  struct Hypre_Pilut__array*  array,
  int32_t                     i1,
  int32_t                     i2,
  int32_t                     i3,
  int32_t                     i4,
  struct Hypre_Pilut__object* value)
{
  struct Hypre_Pilut__object** result = NULL;
  if (array) {
    result = array->d_firstElement;
    switch (array->d_dimen) {
    case 4:
      if ((i4 >= array->d_lower[3]) && (i4 <= array->d_upper[3])) {
        result += (array->d_stride[3]*(i4 - array->d_lower[3]));
      }
      else {
        result = NULL;
        break;
      }
      /* fall through */
    case 3:
      if ((i3 >= array->d_lower[2]) && (i3 <= array->d_upper[2])) {
        result += (array->d_stride[2]*(i3 - array->d_lower[2]));
      }
      else {
        result = NULL;
        break;
      }
      /* fall through */
    case 2:
      if ((i2 >= array->d_lower[1]) && (i2 <= array->d_upper[1])) {
        result += (array->d_stride[1]*(i2 - array->d_lower[1]));
      }
      else {
        result = NULL;
        break;
      }
      /* fall through */
    case 1:
      if ((i1 >= array->d_lower[0]) && (i1 <= array->d_upper[0])) {
        result += (array->d_stride[0]*(i1 - array->d_lower[0]));
      }
      else {
        result = NULL;
        break;
      }
      break;
    default:
      result = NULL;
      break;
    }
  }
  if (result) {
    if (value) {
      (*(value->d_epv->f_addReference))(value);
    }
    if (*result) {
      (*((*result)->d_epv->f_deleteReference))((*result));
    }
    *result = value;
  }
}

/*
 * Return the number of dimensions in the array. If the
 * array pointer is NULL, zero is returned.
 */

int32_t
Hypre_Pilut__iorarray_dimen(const struct Hypre_Pilut__array *array)
{
  return array ? array->d_dimen : 0;
}

/*
 * Return the lower bound on dimension ind. If ind is not
 * a valid dimension, zero is returned.
 */

int32_t
Hypre_Pilut__iorarray_lower(const struct Hypre_Pilut__array *array, int32_t ind)
{
  return (array && (ind < array->d_dimen) && (ind >= 0))
  ? array->d_lower[ind] : 0;
}

/*
 * Return the upper bound on dimension ind. If ind is not
 * a valid dimension, negative one is returned.
 */

int32_t
Hypre_Pilut__iorarray_upper(const struct Hypre_Pilut__array *array, int32_t ind)
{
  return (array && (ind < array->d_dimen) && (ind >= 0))
    ? array->d_upper[ind] : -1;
}

static const struct Hypre_Pilut__external
s_externalEntryPoints = {
  Hypre_Pilut__new,
  Hypre_Pilut__remote,
  Hypre_Pilut__iorarray_create,
  Hypre_Pilut__iorarray_borrow,
  Hypre_Pilut__iorarray_destroy,
  Hypre_Pilut__iorarray_dimen,
  Hypre_Pilut__iorarray_lower,
  Hypre_Pilut__iorarray_upper,
  Hypre_Pilut__iorarray_get,
  Hypre_Pilut__iorarray_get4,
  Hypre_Pilut__iorarray_set,
  Hypre_Pilut__iorarray_set4
};

/*
 * This function returns a pointer to a static structure of
 * pointers to function entry points.  Its purpose is to provide
 * one-stop shopping for loading DLLs.
 * loading DLLs
 */

const struct Hypre_Pilut__external*
Hypre_Pilut__externals(void)
{
  return &s_externalEntryPoints;
}

/*
 * REMOTE CAST: dynamic type casting for remote objects.
 */

static void* remote_Hypre_Pilut__cast(
  struct Hypre_Pilut__object* self,
  const char* name)
{
  return NULL;
}

/*
 * REMOTE DELETE: call the remote destructor for the object.
 */

static void remote_Hypre_Pilut__delete(
  struct Hypre_Pilut__object* self)
{
  free((void*) self);
}

/*
 * REMOTE METHOD STUB:Apply
 */

static int32_t
remote_Hypre_Pilut_Apply(
  struct Hypre_Pilut__object* self,
  struct Hypre_Vector__object* x,
  struct Hypre_Vector__object** y)
{
  return 0;
}

/*
 * REMOTE METHOD STUB:GetResidual
 */

static int32_t
remote_Hypre_Pilut_GetResidual(
  struct Hypre_Pilut__object* self,
  struct Hypre_Vector__object** r)
{
  return 0;
}

/*
 * REMOTE METHOD STUB:SetCommunicator
 */

static int32_t
remote_Hypre_Pilut_SetCommunicator(
  struct Hypre_Pilut__object* self,
  void* comm)
{
  return 0;
}

/*
 * REMOTE METHOD STUB:SetDoubleArrayParameter
 */

static int32_t
remote_Hypre_Pilut_SetDoubleArrayParameter(
  struct Hypre_Pilut__object* self,
  const char* name,
  struct SIDL_double__array* value)
{
  return 0;
}

/*
 * REMOTE METHOD STUB:SetDoubleParameter
 */

static int32_t
remote_Hypre_Pilut_SetDoubleParameter(
  struct Hypre_Pilut__object* self,
  const char* name,
  double value)
{
  return 0;
}

/*
 * REMOTE METHOD STUB:SetIntArrayParameter
 */

static int32_t
remote_Hypre_Pilut_SetIntArrayParameter(
  struct Hypre_Pilut__object* self,
  const char* name,
  struct SIDL_int__array* value)
{
  return 0;
}

/*
 * REMOTE METHOD STUB:SetIntParameter
 */

static int32_t
remote_Hypre_Pilut_SetIntParameter(
  struct Hypre_Pilut__object* self,
  const char* name,
  int32_t value)
{
  return 0;
}

/*
 * REMOTE METHOD STUB:SetLogging
 */

static int32_t
remote_Hypre_Pilut_SetLogging(
  struct Hypre_Pilut__object* self,
  int32_t level)
{
  return 0;
}

/*
 * REMOTE METHOD STUB:SetOperator
 */

static int32_t
remote_Hypre_Pilut_SetOperator(
  struct Hypre_Pilut__object* self,
  struct Hypre_Operator__object* A)
{
  return 0;
}

/*
 * REMOTE METHOD STUB:SetPrintLevel
 */

static int32_t
remote_Hypre_Pilut_SetPrintLevel(
  struct Hypre_Pilut__object* self,
  int32_t level)
{
  return 0;
}

/*
 * REMOTE METHOD STUB:SetStringParameter
 */

static int32_t
remote_Hypre_Pilut_SetStringParameter(
  struct Hypre_Pilut__object* self,
  const char* name,
  const char* value)
{
  return 0;
}

/*
 * REMOTE METHOD STUB:Setup
 */

static int32_t
remote_Hypre_Pilut_Setup(
  struct Hypre_Pilut__object* self)
{
  return 0;
}

/*
 * REMOTE METHOD STUB:addReference
 */

static void
remote_Hypre_Pilut_addReference(
  struct Hypre_Pilut__object* self)
{
}

/*
 * REMOTE METHOD STUB:deleteReference
 */

static void
remote_Hypre_Pilut_deleteReference(
  struct Hypre_Pilut__object* self)
{
}

/*
 * REMOTE METHOD STUB:isInstanceOf
 */

static SIDL_bool
remote_Hypre_Pilut_isInstanceOf(
  struct Hypre_Pilut__object* self,
  const char* name)
{
  return 0;
}

/*
 * REMOTE METHOD STUB:isSame
 */

static SIDL_bool
remote_Hypre_Pilut_isSame(
  struct Hypre_Pilut__object* self,
  struct SIDL_BaseInterface__object* iobj)
{
  return 0;
}

/*
 * REMOTE METHOD STUB:queryInterface
 */

static struct SIDL_BaseInterface__object*
remote_Hypre_Pilut_queryInterface(
  struct Hypre_Pilut__object* self,
  const char* name)
{
  return (struct SIDL_BaseInterface__object*) 0;
}

/*
 * REMOTE EPV: create remote entry point vectors (EPVs).
 */

static void Hypre_Pilut__init_remote_epv(void)
{
  struct Hypre_Pilut__epv*        epv = &s_rem__hypre_pilut;
  struct Hypre_Operator__epv*     e0  = &s_rem__hypre_operator;
  struct Hypre_Solver__epv*       e1  = &s_rem__hypre_solver;
  struct SIDL_BaseClass__epv*     e2  = &s_rem__sidl_baseclass;
  struct SIDL_BaseInterface__epv* e3  = &s_rem__sidl_baseinterface;

  epv->f__cast                   = remote_Hypre_Pilut__cast;
  epv->f__delete                 = remote_Hypre_Pilut__delete;
  epv->f__ctor                   = NULL;
  epv->f__dtor                   = NULL;
  epv->f_Apply                   = remote_Hypre_Pilut_Apply;
  epv->f_GetResidual             = remote_Hypre_Pilut_GetResidual;
  epv->f_SetCommunicator         = remote_Hypre_Pilut_SetCommunicator;
  epv->f_SetDoubleArrayParameter = remote_Hypre_Pilut_SetDoubleArrayParameter;
  epv->f_SetDoubleParameter      = remote_Hypre_Pilut_SetDoubleParameter;
  epv->f_SetIntArrayParameter    = remote_Hypre_Pilut_SetIntArrayParameter;
  epv->f_SetIntParameter         = remote_Hypre_Pilut_SetIntParameter;
  epv->f_SetLogging              = remote_Hypre_Pilut_SetLogging;
  epv->f_SetOperator             = remote_Hypre_Pilut_SetOperator;
  epv->f_SetPrintLevel           = remote_Hypre_Pilut_SetPrintLevel;
  epv->f_SetStringParameter      = remote_Hypre_Pilut_SetStringParameter;
  epv->f_Setup                   = remote_Hypre_Pilut_Setup;
  epv->f_addReference            = remote_Hypre_Pilut_addReference;
  epv->f_deleteReference         = remote_Hypre_Pilut_deleteReference;
  epv->f_isInstanceOf            = remote_Hypre_Pilut_isInstanceOf;
  epv->f_isSame                  = remote_Hypre_Pilut_isSame;
  epv->f_queryInterface          = remote_Hypre_Pilut_queryInterface;

  e0->f__cast                   = (void* (*)(void*,const char*)) epv->f__cast;
  e0->f__delete                 = (void (*)(void*)) epv->f__delete;
  e0->f_Apply                   = (int32_t (*)(void*,
    struct Hypre_Vector__object*,struct Hypre_Vector__object**)) epv->f_Apply;
  e0->f_SetCommunicator         = (int32_t (*)(void*,
    void*)) epv->f_SetCommunicator;
  e0->f_SetDoubleArrayParameter = (int32_t (*)(void*,const char*,
    struct SIDL_double__array*)) epv->f_SetDoubleArrayParameter;
  e0->f_SetDoubleParameter      = (int32_t (*)(void*,const char*,
    double)) epv->f_SetDoubleParameter;
  e0->f_SetIntArrayParameter    = (int32_t (*)(void*,const char*,
    struct SIDL_int__array*)) epv->f_SetIntArrayParameter;
  e0->f_SetIntParameter         = (int32_t (*)(void*,const char*,
    int32_t)) epv->f_SetIntParameter;
  e0->f_SetStringParameter      = (int32_t (*)(void*,const char*,
    const char*)) epv->f_SetStringParameter;
  e0->f_Setup                   = (int32_t (*)(void*)) epv->f_Setup;
  e0->f_addReference            = (void (*)(void*)) epv->f_addReference;
  e0->f_deleteReference         = (void (*)(void*)) epv->f_deleteReference;
  e0->f_isInstanceOf            = (SIDL_bool (*)(void*,
    const char*)) epv->f_isInstanceOf;
  e0->f_isSame                  = (SIDL_bool (*)(void*,
    struct SIDL_BaseInterface__object*)) epv->f_isSame;
  e0->f_queryInterface          = (struct SIDL_BaseInterface__object* (*)(void*,
    const char*)) epv->f_queryInterface;

  e1->f__cast                   = (void* (*)(void*,const char*)) epv->f__cast;
  e1->f__delete                 = (void (*)(void*)) epv->f__delete;
  e1->f_Apply                   = (int32_t (*)(void*,
    struct Hypre_Vector__object*,struct Hypre_Vector__object**)) epv->f_Apply;
  e1->f_GetResidual             = (int32_t (*)(void*,
    struct Hypre_Vector__object**)) epv->f_GetResidual;
  e1->f_SetCommunicator         = (int32_t (*)(void*,
    void*)) epv->f_SetCommunicator;
  e1->f_SetDoubleArrayParameter = (int32_t (*)(void*,const char*,
    struct SIDL_double__array*)) epv->f_SetDoubleArrayParameter;
  e1->f_SetDoubleParameter      = (int32_t (*)(void*,const char*,
    double)) epv->f_SetDoubleParameter;
  e1->f_SetIntArrayParameter    = (int32_t (*)(void*,const char*,
    struct SIDL_int__array*)) epv->f_SetIntArrayParameter;
  e1->f_SetIntParameter         = (int32_t (*)(void*,const char*,
    int32_t)) epv->f_SetIntParameter;
  e1->f_SetLogging              = (int32_t (*)(void*,
    int32_t)) epv->f_SetLogging;
  e1->f_SetOperator             = (int32_t (*)(void*,
    struct Hypre_Operator__object*)) epv->f_SetOperator;
  e1->f_SetPrintLevel           = (int32_t (*)(void*,
    int32_t)) epv->f_SetPrintLevel;
  e1->f_SetStringParameter      = (int32_t (*)(void*,const char*,
    const char*)) epv->f_SetStringParameter;
  e1->f_Setup                   = (int32_t (*)(void*)) epv->f_Setup;
  e1->f_addReference            = (void (*)(void*)) epv->f_addReference;
  e1->f_deleteReference         = (void (*)(void*)) epv->f_deleteReference;
  e1->f_isInstanceOf            = (SIDL_bool (*)(void*,
    const char*)) epv->f_isInstanceOf;
  e1->f_isSame                  = (SIDL_bool (*)(void*,
    struct SIDL_BaseInterface__object*)) epv->f_isSame;
  e1->f_queryInterface          = (struct SIDL_BaseInterface__object* (*)(void*,
    const char*)) epv->f_queryInterface;

  e2->f__cast           = (void* (*)(struct SIDL_BaseClass__object*,
    const char*)) epv->f__cast;
  e2->f__delete         = (void (*)(struct SIDL_BaseClass__object*)) 
    epv->f__delete;
  e2->f_addReference    = (void (*)(struct SIDL_BaseClass__object*)) 
    epv->f_addReference;
  e2->f_deleteReference = (void (*)(struct SIDL_BaseClass__object*)) 
    epv->f_deleteReference;
  e2->f_isInstanceOf    = (SIDL_bool (*)(struct SIDL_BaseClass__object*,
    const char*)) epv->f_isInstanceOf;
  e2->f_isSame          = (SIDL_bool (*)(struct SIDL_BaseClass__object*,
    struct SIDL_BaseInterface__object*)) epv->f_isSame;
  e2->f_queryInterface  = (struct SIDL_BaseInterface__object* (*)(struct 
    SIDL_BaseClass__object*,const char*)) epv->f_queryInterface;

  e3->f__cast           = (void* (*)(void*,const char*)) epv->f__cast;
  e3->f__delete         = (void (*)(void*)) epv->f__delete;
  e3->f_addReference    = (void (*)(void*)) epv->f_addReference;
  e3->f_deleteReference = (void (*)(void*)) epv->f_deleteReference;
  e3->f_isInstanceOf    = (SIDL_bool (*)(void*,
    const char*)) epv->f_isInstanceOf;
  e3->f_isSame          = (SIDL_bool (*)(void*,
    struct SIDL_BaseInterface__object*)) epv->f_isSame;
  e3->f_queryInterface  = (struct SIDL_BaseInterface__object* (*)(void*,
    const char*)) epv->f_queryInterface;

  s_remote_initialized = 1;
}

/*
 * REMOTE: generate remote instance given URL string.
 */

struct Hypre_Pilut__object*
Hypre_Pilut__remote(const char *url)
{
  struct Hypre_Pilut__object* self =
    (struct Hypre_Pilut__object*) malloc(
      sizeof(struct Hypre_Pilut__object));

  struct Hypre_Pilut__object*    s0 = self;
  struct SIDL_BaseClass__object* s1 = &s0->d_sidl_baseclass;

  if (!s_remote_initialized) {
    Hypre_Pilut__init_remote_epv();
  }

  s1->d_sidl_baseinterface.d_epv    = &s_rem__sidl_baseinterface;
  s1->d_sidl_baseinterface.d_object = NULL; /* FIXME */

  s1->d_data = NULL; /* FIXME */
  s1->d_epv  = &s_rem__sidl_baseclass;

  s0->d_hypre_operator.d_epv    = &s_rem__hypre_operator;
  s0->d_hypre_operator.d_object = NULL; /* FIXME */

  s0->d_hypre_solver.d_epv    = &s_rem__hypre_solver;
  s0->d_hypre_solver.d_object = NULL; /* FIXME */

  s0->d_data = NULL; /* FIXME */
  s0->d_epv  = &s_rem__hypre_pilut;

  return self;
}
