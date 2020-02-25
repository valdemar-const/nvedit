#include "EditorWindow.hpp"

#include <FL/Fl_Text_Buffer.H>
#include <FL/filename.H>

EditorWindow::FileTab::FileTab(int x, int y, int w, int h, const std::string &path)
        : Fl_Text_Editor(x, y, w, h) {
    // buffer_ = new Fl_Text_Buffer();
    buffer(new Fl_Text_Buffer());
    textfont(FL_COURIER);
    box(FL_NO_BOX);
    if (!path.empty()) {
        // if have path, load text from file and get name from path string
        buffer()->loadfile(path.data());
        full_path_ = path;
        label(strdup(fl_filename_name(full_path_.data())));
    } else {
        label(get_new_name());
    }
}

EditorWindow::FileTab::~FileTab() {
    free((void *)label());
    delete buffer();
    buffer(0);
}

void EditorWindow::FileTab::save_path(const std::string &new_path) {
    full_path_ = new_path;
    buffer()->savefile(new_path.data());
    free((void *)label());
    label(strdup(fl_filename_name(full_path_.data())));
}