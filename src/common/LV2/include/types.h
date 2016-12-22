#define NS_RDF "http://www.w3.org/1999/02/22-rdf-syntax-ns#"
#define NS_XSD "http://www.w3.org/2001/XMLSchema#"

#ifndef MIN
#    define MIN(a, b) (((a) < (b)) ? (a) : (b))
#endif

#ifndef MAX
#    define MAX(a, b) (((a) > (b)) ? (a) : (b))
#endif

#ifdef __clang__
#    define REALTIME __attribute__((annotate("realtime")))
#else
#    define REALTIME
#endif

/* Size factor for UI ring buffers.  The ring size is a few times the size of
   an event output to give the UI a chance to keep up.  Experiments with Ingen,
   which can highly saturate its event output, led me to this value.  It
   really ought to be enough for anybody(TM).
*/
#define N_BUFFER_CYCLES 16

  /**< Exit semaphore */

//static LV2_URID map_uri(
    //LV2_URID_Map_Handle handle,
    //const char * uri
//) {
	//zix_sem_wait(&jalv->symap_lock);
	//const LV2_URID id = symap_map(jalv->symap, uri);
	//zix_sem_post(&jalv->symap_lock);
	//return id;
//}

//static const char*
//unmap_uri(LV2_URID_Unmap_Handle handle,
          //LV2_URID              urid)
//{
	//Jalv* jalv = (Jalv*)handle;
	//zix_sem_wait(&jalv->symap_lock);
	//const char* uri = symap_unmap(jalv->symap, urid);
	//zix_sem_post(&jalv->symap_lock);
	//return uri;
//}

/**
   Map function for URI map extension.
*/
//static uint32_t uri_to_id(LV2_URI_Map_Callback_Data callback_data,
          //const char*               map,
          //const char*               uri)
//{
//	Jalv* jalv = (Jalv*)callback_data;
	//zix_sem_wait(&jalv->symap_lock);
	//const LV2_URID id = symap_map(symap, uri);
	//zix_sem_post(&jalv->symap_lock);
	//return id;
//}
