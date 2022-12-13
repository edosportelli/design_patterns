#include <iostream>
#include <list>
#include <string>

class FileBase
{
  public:
    FileBase() = default;
    FileBase(const std::string name) : name_(name){};

    virtual void Add(FileBase* file) = 0;
    virtual void Remove(FileBase* file) = 0;
    std::string Name() const { return name_; }
    void SetParent(FileBase* parent) { parent_ = parent; }

  protected:
    std::string name_;
    FileBase* parent_{nullptr};
};

class Folder : public FileBase
{
  public:
    Folder(const std::string name) : FileBase(name){};
    Folder(const Folder& source)
    {
        for (auto item : source.children_)
            this->children_.push_back(item);
        this->name_ = source.name_;
    }

    virtual void Add(FileBase* file) override;
    virtual void Remove(FileBase* file) override;
    void Draw(std::string space_string) const;

  protected:
    std::list<FileBase*> children_;
};

class File : public FileBase
{
  public:
    File(const std::string name) : FileBase(name){};
    File(const File& source) { this->name_ = source.name_; }

    virtual void Add(FileBase* file) override;
    virtual void Remove(FileBase* file) override;
};
