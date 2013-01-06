#ifndef _UMLBASEPACKAGE_H
#define _UMLBASEPACKAGE_H


#include "UmlItem.h"
#include "anItemKind.h"
#include <q3cstring.h>

class UmlPackage;
class UmlDiagram;

//  Manage the packages
class UmlBasePackage : public UmlItem
{
public:
    // returns a new package named 'name' created under 'parent'
    //
    // In case it cannot be created (the name is already used or
    // invalid, 'parent' cannot contain it etc ...) return 0 in C++
    // and produce a RuntimeException in Java
    static UmlPackage * create(UmlPackage * parent, const char * name);

    // returns the kind of the item
    virtual anItemKind kind();

    // returns the optional associated diagram
    UmlDiagram * associatedDiagram();

    // sets the associated diagram, arg may be null to unset it
    //
    // On error return FALSE in C++, produce a RuntimeException in Java
    bool set_AssociatedDiagram(UmlDiagram * d);

    // Import a project in the current package
    // fn is the pathname of the .prj file of the project to import
    // or an empty string (the project will be set through a dialog)
    // Return the new UmlPackage containing the imported project, or
    // 0/null on error
    UmlPackage * importProject(const Q3CString & fn);

#ifdef WITHCPP
    // returns the path where the C++ source files are generated by the
    // c++ generator.
    const Q3CString & cppSrcDir();

    // to set the path where the C++ source files are generated by the
    // C++ generator, may be relative even the 'root' path is not
    // (already) an absolute path
    //
    // On error return FALSE in C++, produce a RuntimeException in Java
    bool set_CppSrcDir(const Q3CString & s);

    // returns the path where the C++ header files are generated by the
    // C++ generator.
    const Q3CString & cppHDir();

    // to set the path where the C++ header files are generated by the
    // C++ generator, may be relative even the 'root' path is not
    // (already) an absolute path
    //
    // On error return FALSE in C++, produce a RuntimeException in Java
    bool set_CppHDir(const Q3CString & s);

    //returns the namespace name associed to the package
    Q3CString cppNamespace();

    //to set the namespace name associed to the package.
    //
    // On error return FALSE in C++, produce a RuntimeException in Java
    bool set_CppNamespace(const Q3CString & s);

    // returns a sub package of the current one having the c++ namespace 'n'
    // (including the current one), else 0/null
    UmlPackage * findCppNamespace(const Q3CString & n) const;
#endif

#ifdef WITHJAVA
    // returns the path where the JAVA files are generated by the
    // JAVA generator.
    const Q3CString & javaDir();

    // to set the path where the JAVA files are generated by the
    // JAVA generator, may be relative even the 'root' path is not
    // (already) an absolute path
    //
    // On error return FALSE in C++, produce a RuntimeException in Java
    bool set_JavaDir(const Q3CString & s);

    //returns the java package name associed to the package
    Q3CString javaPackage();

    // to set the java package name associed to the package.
    //
    // On error return FALSE in C++, produce a RuntimeException in Java
    bool set_JavaPackage(const Q3CString & s);

    // returns a sub package of the current one having the Java package 'n'
    // (including the current one), else 0/null
    UmlPackage * findJavaPackage(const Q3CString & n) const;
#endif

#ifdef WITHPHP
    // returns the path where the PHP files are generated by the
    // PHP generator.
    const Q3CString & phpDir();

    // to set the path where the PHP files are generated by the
    // PHP generator, may be relative even the 'root' path is not
    // (already) an absolute path
    //
    // On error return FALSE in C++, produce a RuntimeException in Java
    bool set_PhpDir(const Q3CString & s);
    // return the namespace name associed to the package

    const Q3CString & phpNamespace();

    // the namespace name associed to the package.
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    bool set_PhpNamespace(const Q3CString & v);

    // returns a sub package of the current one having the php namespace 'n'
    // (including the current one), else 0/null

    UmlPackage * findPhpNamespace(const Q3CString & n);
#endif

#ifdef WITHPYTHON
    // returns the path where the PYTHON files are generated by the
    // PYTHON generator.
    const Q3CString & pythonDir();

    // to set the path where the PYTHON files are generated by the
    // PYTHON generator, may be relative even the 'root' path is not
    // (already) an absolute path
    //
    // On error return FALSE in C++, produce a RuntimeException in Java
    bool set_PythonDir(const Q3CString & s);

    //returns the python package name associed to the package
    Q3CString pythonPackage();

    // to set the python package name associed to the package.
    //
    // On error return FALSE in C++, produce a RuntimeException in Java
    bool set_PythonPackage(const Q3CString & s);

    // returns a sub package of the current one having the Python package 'n'
    // (including the current one), else 0/null
    UmlPackage * findPythonPackage(const Q3CString & n) const;
#endif

#ifdef WITHIDL
    // returns the path where the IDL files are generated by the
    // IDL generator.
    const Q3CString & idlDir();

    // to set the path where the IDL files are generated by the
    // IDL generator, may be relative even the 'root' path is not
    // (already) an absolute path
    //
    // On error return FALSE in C++, produce a RuntimeException in Java
    bool set_IdlDir(const Q3CString & s);

    //returns the module name associed to the package
    Q3CString idlModule();

    // to set the module name associed to the package.
    //
    // On error return FALSE in C++, produce a RuntimeException in Java
    bool set_IdlModule(const Q3CString & s);

    // returns a sub package of the current one having the IDL module 'n'
    // (including the current one), else 0/null
    UmlPackage * findIdlModule(const Q3CString & n) const;
#endif

    //  Returns the project
    static UmlPackage * getProject();

    //return TRUE in case something is modified (i.e. the project must be saved)

    static bool isProjectModified();

    //save the project if needed
    static void saveProject();

    //Does nothing in case an edition is on going under BOUML. Else :
    //close the current project (in case it is not saved the last modifications are lost),
    //load the specified one, and all the communications with the plug-outs including the
    //current one are closed.

    static void loadProject(Q3CString p);

    // Force consistency concerning the profiles and their stereotypes

    static void updateProfiles();

    // to unload the object to free memory, it will be reloaded automatically
    // if needed. Recursively done for the sub items if 'rec' is TRUE.
    //
    // if 'del' is true the sub items are deleted in C++, and removed from the
    // internal dictionnary in C++ and Java (to allow it to be garbaged),
    // you will have to call Children() to re-access to them
    virtual void unload(bool rec = FALSE, bool del = FALSE);


private:
    UmlDiagram * _assoc_diagram;

#ifdef WITHCPP
    Q3CString _cpp_src_dir;

    Q3CString _cpp_h_dir;

    Q3CString _cpp_namespace;
#endif


#ifdef WITHJAVA
    Q3CString _java_dir;

    Q3CString _java_package;
#endif


#ifdef WITHPHP
    Q3CString _php_dir;
    Q3CString _php_namespace;
#endif

#ifdef WITHPYTHON
    Q3CString _python_dir;

    Q3CString _python_package;
#endif

#ifdef WITHIDL
    Q3CString _idl_dir;

    Q3CString _idl_module;
#endif



protected:
    //internal, do NOT use it

    virtual void read_uml_();

#ifdef WITHCPP
    //internal, do NOT use it

    virtual void read_cpp_();
#endif

#ifdef WITHJAVA
    //internal, do NOT use it

    virtual void read_java_();
#endif

#ifdef WITHPHP
    //internal, do NOT use it

    virtual void read_php_();
#endif

#ifdef WITHPYTHON
    //internal, do NOT use it

    virtual void read_python_();
#endif

#ifdef WITHIDL
    //internal, do NOT use it

    virtual void read_idl_();
#endif

    // the constructor, do not call it yourself !!!!!!!!!!
    UmlBasePackage(void * id, const Q3CString & n);

};

inline UmlBasePackage::UmlBasePackage(void * id, const Q3CString & n) : UmlItem(id, n)
{
    _assoc_diagram = 0;
}

#endif
