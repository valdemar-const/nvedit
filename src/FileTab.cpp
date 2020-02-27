#include "EditorWindow.hpp"

#include <FL/Fl_Text_Buffer.H>
#include <FL/filename.H>

EditorWindow::FileTab::FileTab(int x, int y, int w, int h, const std::string &path)
        : Fl_Group(x, y, w, h) {
    buffer_ = new Fl_Text_Buffer();
    begin();
    editor_ = new Fl_Text_Editor(x, y, w, h);
    editor_->textfont(FL_COURIER);
    editor_->box(FL_NO_BOX);
    editor_->labeltype(FL_NO_LABEL);
    editor_->buffer(buffer_);
    end();
    resizable(editor_);
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
    editor_->buffer(0);
}

void EditorWindow::FileTab::save_path(const std::string &new_path = {}) {
    if (!new_path.empty()) {
        full_path_ = new_path;
    } else if (!full_path_.empty()) {
        editor_->buffer()->savefile(full_path_.data());
        free((void *)label());
        label(strdup(fl_filename_name(full_path_.data())));
    } else
        return;
}