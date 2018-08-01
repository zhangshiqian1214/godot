/*************************************************************************/
/*  image_loader.h                                                       */
/*************************************************************************/
/*                       This file is part of:                           */
/*                           GODOT ENGINE                                */
/*                      https://godotengine.org                          */
/*************************************************************************/
/* Copyright (c) 2007-2018 Juan Linietsky, Ariel Manzur.                 */
/* Copyright (c) 2014-2018 Godot Engine contributors (cf. AUTHORS.md)    */
/*                                                                       */
/* Permission is hereby granted, free of charge, to any person obtaining */
/* a copy of this software and associated documentation files (the       */
/* "Software"), to deal in the Software without restriction, including   */
/* without limitation the rights to use, copy, modify, merge, publish,   */
/* distribute, sublicense, and/or sell copies of the Software, and to    */
/* permit persons to whom the Software is furnished to do so, subject to */
/* the following conditions:                                             */
/*                                                                       */
/* The above copyright notice and this permission notice shall be        */
/* included in all copies or substantial portions of the Software.       */
/*                                                                       */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,       */
/* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF    */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.*/
/* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY  */
/* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,  */
/* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE     */
/* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                */
/*************************************************************************/

#ifndef IMAGE_LOADER_H
#define IMAGE_LOADER_H

#include "image.h"
#include "io/resource_loader.h"
#include "list.h"
#include "os/file_access.h"
#include "ustring.h"

/**
	@author Juan Linietsky <reduzio@gmail.com>
*/

/**
 * @class ImageScanLineLoader
 * @author Juan Linietsky <reduzio@gmail.com>
 *

 */
class ImageLoader;

/**
 * @class ImageLoader
 * Base Class and singleton for loading images from disk
 * Can load images in one go, or by scanline
 */

class ImageFormatLoader {
	friend class ImageLoader;
	friend class ResourceFormatLoaderImage;

protected:
	virtual Error load_image(Ref<Image> p_image, FileAccess *p_fileaccess, bool p_force_linear, float p_scale) = 0;
	virtual void get_recognized_extensions(List<String> *p_extensions) const = 0;
	bool recognize(const String &p_extension) const;

public:
	virtual ~ImageFormatLoader() {}
};

class ImageLoader {

	enum {
		MAX_LOADERS = 8
	};
	friend class ResourceFormatLoaderImage;
	static ImageFormatLoader *loader[MAX_LOADERS];
	static int loader_count;

protected:
public:
	static Error load_image(String p_file, Ref<Image> p_image, FileAccess *p_custom = NULL, bool p_force_linear = false, float p_scale = 1.0);
	static void get_recognized_extensions(List<String> *p_extensions);
	static bool recognize(const String &p_extension);

	static void add_image_format_loader(ImageFormatLoader *p_loader);
};

class ResourceFormatLoaderImage : public ResourceFormatLoader {
public:
	virtual RES load(const String &p_path, const String &p_original_path = "", Error *r_error = NULL);
	virtual void get_recognized_extensions(List<String> *p_extensions) const;
	virtual bool handles_type(const String &p_type) const;
	virtual String get_resource_type(const String &p_path) const;
};

#endif
