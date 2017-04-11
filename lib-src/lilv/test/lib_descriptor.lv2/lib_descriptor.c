/*
  Lilv Test Plugin - Missing descriptor
  Copyright 2011-2015 David Robillard <d@drobilla.net>

  Permission to use, copy, modify, and/or distribute this software for any
  purpose with or without fee is hereby granted, provided that the above
  copyright notice and this permission notice appear in all copies.

  THIS SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
  WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
  MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
  ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
  WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
  ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
  OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
*/

#include <stdlib.h>

#include "lv2/lv2plug.in/ns/lv2core/lv2.h"

#define PLUGIN_URI "http://example.org/lib-descriptor"

enum {
	TEST_INPUT  = 0,
	TEST_OUTPUT = 1
};

typedef struct {
	float* input;
	float* output;
} Test;

static void
cleanup(LV2_Handle instance)
{
	free((Test*)instance);
}

static void
connect_port(LV2_Handle instance, uint32_t port, void* data)
{
	Test* test = (Test*)instance;
	switch (port) {
	case TEST_INPUT:
		test->input = (float*)data;
		break;
	case TEST_OUTPUT:
		test->output = (float*)data;
		break;
	default:
		break;
	}
}

static LV2_Handle
instantiate(const LV2_Descriptor*     descriptor,
            double                    rate,
            const char*               path,
            const LV2_Feature* const* features)
{
	Test* test = (Test*)calloc(1, sizeof(Test));
	if (!test) {
		return NULL;
	}

	return (LV2_Handle)test;
}

static void
run(LV2_Handle instance, uint32_t sample_count)
{
	Test* test = (Test*)instance;

	*test->output = *test->input;
}

static const LV2_Descriptor descriptor = {
	PLUGIN_URI,
	instantiate,
	connect_port,
	NULL, // activate,
	run,
	NULL, // deactivate,
	cleanup,
	NULL  // extension_data
};

static const LV2_Descriptor*
get_plugin(LV2_Lib_Handle handle, uint32_t index)
{
	switch (index) {
	case 0:
		return &descriptor;
	default:
		return NULL;
	}
}

static const LV2_Lib_Descriptor lib = {
	NULL,
	sizeof(LV2_Lib_Descriptor),
	NULL,
	get_plugin };

LV2_SYMBOL_EXPORT
const LV2_Lib_Descriptor*
lv2_lib_descriptor(const char*              bundle_path,
                   const LV2_Feature*const* features)
{
	return &lib;
}
