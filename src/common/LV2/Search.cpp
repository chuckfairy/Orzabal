/**
 * Search func
 */
#include <stdio.h>
#include <string.h>
#include <vector>
#include <sstream>

#include <lilv/lilv.h>

#include "lilv_config.h"

#include "Search.h"


LV2Search::LV2Search() {};

//void LV2Search::listPlugins(const LilvPlugins* list, bool show_names)
//{
//	LILV_FOREACH(plugins, i, list) {
//		const LilvPlugin* p = lilv_plugins_get(list, i);
//		if (show_names) {
//			LilvNode* n = lilv_plugin_get_name(p);
//			printf("%s\n", lilv_node_as_string(n));
//			lilv_node_free(n);
//		} else {
//			printf("%s\n", lilv_node_as_uri(lilv_plugin_get_uri(p)));
//		}
//	}
//}
//


<vector, LV2Plugin> LV2Search::findAll() {

	LilvWorld* world = lilv_world_new();
	lilv_world_load_all(world);

	const LilvPlugins* plugins = lilv_world_get_all_plugins(world);

	list_plugins(plugins, show_names);

	lilv_world_free(world);

	return 0;
}
