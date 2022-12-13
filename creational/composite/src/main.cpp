#include "file.hpp"
#include "vector"
#include <iostream>

std::vector<std::string> system_folders{"usr", "bin", "opt", "etc", "User", "mnt", "boot", "home"};
std::vector<std::string> documents{"text1", "text2", "CV"};
std::vector<std::string> pictures{"foto1.pnj", "foto2.pnj"};

int main()
{
    // we are doing deep copies, so the order we add the folders matter
    Folder Documents{"Documents"};
    for (auto& item : documents)
    {
        File file = File(item);
        Documents.Add(&file);
    }

    Folder Pictures("Pictures");
    for (auto& item : pictures)
    {
        File file = File(item);
        Pictures.Add(&file);
    }

    Folder Edoardo{"Edoardo"};
    Edoardo.Add(&Pictures);
    Edoardo.Add(&Documents);

    Folder root{"root"};
    for (auto& item : system_folders)
    {
        Folder folder = Folder(item);
        if (folder.Name() == "User")
            folder.Add(&Edoardo);

        root.Add(&folder);
    }

    // drawing first
    std::string space_string{""};
    root.Draw(space_string);

    std::cout << std::endl;
    // drawing after removing
    Folder remove("foto1.pnj");
    root.Remove(&remove);
    root.Draw(space_string);
}