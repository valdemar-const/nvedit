#include "EditorWindow.hpp"

#include <FL/Fl_Text_Buffer.H>
#include <FL/filename.H>

EditorWindow::FileTab::FileTab(int x, int y, int w, int h, const std::string &path)
        : Fl_Group(x, y, w, h) {
    editor_ = new Fl_Text_Editor(x, y, w, h);
    Fl_Text_Buffer *new_buffer = new Fl_Text_Buffer;
    editor_->buffer(new_buffer);
    editor_->textfont(FL_COURIER);
    editor_->box(FL_NO_BOX);
    if (!path.empty()) {
		// if have path, load text from file and get name from path string
        editor_->buffer()->loadfile(path.data());
        full_path_ = path;
        label(strdup(fl_filename_name(full_path_.data())));
    } else {
        label(get_new_name());
    }
}

EditorWindow::FileTab::~FileTab() {
    free((void *)label());
    delete editor_->buffer();
}

void EditorWindow::FileTab::full_path(const std::string &new_path) {
    full_path_ = new_path;
    editor_->buffer()->savefile(new_path.data());
    free((void*)label());
    label(strdup(fl_filename_name(full_path_.data())));
}