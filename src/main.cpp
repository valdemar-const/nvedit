#include "EditorWindow.hpp"

#include <FL/Fl.H>

int main(int argc, char *argv[]) {
    Fl::scheme("gtk+");
    EditorWindow main_window(640, 480, "Text Editor");
    return Fl::run();
}