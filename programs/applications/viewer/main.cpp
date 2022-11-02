/* SPDX-License-Identifier: GPL-3.0-or-later */
/* Copyright © 2016-2022 Byteduck */
#include <libui/libui.h>
#include <libui/widget/Label.h>
#include <libui/widget/Image.h>
#include <libui/bits/FilePicker.h>

using namespace Duck;

int main(int argc, char** argv, char** envp) {
	UI::init(argv, envp);

	Duck::Path image_path = "/";
	if(argc < 2) {
		auto files = UI::FilePicker::make()->pick();
		if(!files.empty())
			image_path = files[0];
		Duck::Log::dbgf("PICKED {}", files[0]);
	} else {
		image_path = argv[1];
	}

	auto window = UI::Window::make();
	auto image = Gfx::Image::load(image_path);

	if(image.is_error()) {
		window->set_contents(UI::Label::make(image.message()));
	} else {
		window->set_contents(UI::Image::make(image.value()));
	}

	window->set_title("Viewer: " + std::string(image.has_value() ? image_path : "No Image"));
	window->set_resizable(true);
	window->show();


	auto disp_rect = Gfx::Rect {{0,0 }, UI::pond_context->get_display_dimensions()};
	if(!disp_rect.contains({{0, 0}, window->dimensions()}))
		window->resize(UI::pond_context->get_display_dimensions());

	UI::run();
}