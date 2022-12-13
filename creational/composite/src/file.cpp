#include "file.hpp"
#include <iostream>
#include <stdexcept>

void File::Add(FileBase* file)
{
    throw std::runtime_error("You cannot add a file in another file! It must be a foler");
}

void File::Remove(FileBase* file)
{
    throw std::runtime_error("You cannot remove a file in another file! It must be a foler");
}

void Folder::Add(FileBase* file)
{
    FileBase* child;    // needed to to a deep copy

    if (File* child_file = dynamic_cast<File*>(file); child_file != nullptr)
    {
        // std::cout << "Adding file " << child_file->Name() << " in folder " << this->Name() << std::endl;
        child = new File(*child_file);
    }
    else if (Folder* child_folder = dynamic_cast<Folder*>(file); child_folder != nullptr)
    {
        // std::cout << "Adding folder " << child_folder->Name() << " in folder " << this->Name() << std::endl;
        child = new Folder(*child_folder);
    }

    child->SetParent(this);
    children_.push_back(child);
}

// In this method we don't take care of removing the subfolders memory
void Folder::Remove(FileBase* file)
{
    for (auto it = children_.begin(); it != children_.end(); it++)
    {
        if ((*it)->Name() == file->Name())
        {
            it = children_.erase(it);
        }
        else
        {
            if (Folder* child = dynamic_cast<Folder*>(*it); child != nullptr)
            {
                child->Remove(file);
            }
        }
    }
}

void Folder::Draw(std::string space_string) const
{
    std::cout << space_string + this->Name() << std::endl;
    space_string += "  ";

    for (auto& item : children_)
    {
        if (Folder* child = dynamic_cast<Folder*>(item); child != nullptr)
        {
            child->Draw(space_string);
        }
        else
        {
            std::cout << space_string + item->Name() << std::endl;
        }
    }
}