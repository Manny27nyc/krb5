/*
 * $Source$
 * $Author$
 *
 * Copyright 1989,1990 by the Massachusetts Institute of Technology.
 *
 * For copying and distribution information, please see the file
 * <krb5/copyright.h>.
 *
 * Glue between Kerberos version and ISODE 6.0 version of structures.
 */

#if !defined(lint) && !defined(SABER)
static char rcsid_klsrq2lsrq_c[] =
"$Id$";
#endif	/* lint || saber */

#include <krb5/copyright.h>
#include <krb5/krb5.h>

/*#include <time.h> */
#include <isode/psap.h>
#include <krb5/asn1.h>
#include "asn1glue.h"

#include <krb5/ext-proto.h>

/* ISODE defines max(a,b) */

struct type_KRB5_LastReq *
krb5_last_req2KRB5_LastReq(val, error)
register krb5_last_req_entry * const *val;
register int *error;
{
#if 0
    /* this code is for -h2 style ISODE structures.  However, pepsy
       generates horribly broken when given -h2. */

    register struct type_KRB5_LastReq *retval;
    register krb5_last_req_entry * const *temp;
    register int i;

    /* count elements */
    for (i = 0, temp = val; *temp; temp++,i++);

    retval = (struct type_KRB5_LastReq *)
	xmalloc(sizeof(*retval) + max(0,i-1)*sizeof(retval->element_KRB5_4[0]));
    if (!retval) {
	*error = ENOMEM;
	return(0);
    }
    xbzero(retval, sizeof(*retval));
    retval->nelem = i;
    for (i = 0; i < retval->nelem; i++) {
	retval->element_KRB5_4[i] = (struct element_KRB5_5 *)
	    xmalloc(sizeof(*(retval->element_KRB5_4[i])));
	if (!retval->element_KRB5_4[i]) {
	    *error = ENOMEM;
	errout:
	    retval->nelem = i;
	    free_KRB5_LastReq(retval);
	    return(0);
	}	    
	retval->element_KRB5_4[i]->lr__type = val[i]->lr_type;
	retval->element_KRB5_4[i]->lr__value = unix2gentime(val[i]->value,
							    error);
	if (!retval->element_KRB5_4[i]->lr__value) {
	    goto errout;
	}
    }
    return(retval);
#endif
    register struct type_KRB5_LastReq *retval = 0, *rv1 = 0, *rv2;
    register krb5_last_req_entry * const *temp;
    register int i;

    /* count elements */
    for (i = 0, temp = val; *temp; temp++,i++, rv1 = rv2) {

	rv2 = (struct type_KRB5_LastReq *) xmalloc(sizeof(*rv2));
	if (!rv2) {
	    if (retval)
		free_KRB5_LastReq(retval);
	    *error = ENOMEM;
	    return(0);
	}
	if (rv1)
	    rv1->next = rv2;
	xbzero((char *)rv2, sizeof (*rv2));
	if (!retval)
	    retval = rv2;

	rv2->element_KRB5_4 = (struct element_KRB5_5 *)
	    xmalloc(sizeof(*(retval->element_KRB5_4)));
	if (!rv2->element_KRB5_4) {
	errout:
	    *error = ENOMEM;
	    if (retval)
		free_KRB5_LastReq(retval);
	    return(0);
	}	    
	rv2->element_KRB5_4->lr__type = val[i]->lr_type;
	rv2->element_KRB5_4->lr__value = unix2gentime(val[i]->value,
						      error);
	if (!retval->element_KRB5_4->lr__value) {
	    goto errout;
	}
    }
    return(retval);
}
