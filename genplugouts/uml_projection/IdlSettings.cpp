#ifdef WITHIDL


#include "IdlSettings.h"

#include "UmlCom.h"
#include "UmlSettings.h"
#include "Tools/ApiCmd.h"
#include "UmlBuiltin.h"
#include "UmlStereotype.h"
//Added by qt3to4:
#include <QByteArray>
bool IdlSettings::useDefaults()
{
    UmlCom::send_cmd(idlSettingsCmd, getIdlUseDefaultsCmd);
    return UmlCom::read_bool();
}

bool IdlSettings::set_UseDefaults(bool y)
{
    UmlCom::send_cmd(idlSettingsCmd, setIdlUseDefaultsCmd, (char) y);
    return UmlCom::read_bool();
}

QByteArray IdlSettings::type(QByteArray s)
{
    read_if_needed_();

    UmlBuiltin * b = UmlSettings::_map_builtins.value(s);

    return (b) ? b->idl : s;
}

bool IdlSettings::set_Type(QByteArray s, QByteArray v)
{
    read_if_needed_();
    UmlCom::send_cmd(idlSettingsCmd, setIdlTypeCmd, (const char *)s, (const char *)v); //[rageek] Fix prototype

    if (UmlCom::read_bool()) {
        UmlBuiltin * b = UmlSettings::_map_builtins.value(s);

        if (b == 0)
            b = UmlSettings::add_type(s);

        b->idl = v;

        return TRUE;
    }
    else
        return FALSE;
}

QByteArray IdlSettings::umlType(QByteArray s)
{
    read_if_needed_();

    return UmlSettings::uml_type(s, &UmlBuiltin::idl);
}

QByteArray IdlSettings::relationAttributeStereotype(const QByteArray & s)
{
    read_if_needed_();

    UmlStereotype * b = UmlSettings::_map_relation_attribute_stereotypes.value(s);

    return (b) ? b->idl : s;
}

bool IdlSettings::set_RelationAttributeStereotype(QByteArray s, QByteArray v)
{
    read_if_needed_();
    UmlCom::send_cmd(idlSettingsCmd, setIdlRelationAttributeStereotypeCmd, (const char *)s, (const char *)v); //[rageek] Fix prototype

    if (UmlCom::read_bool()) {
        UmlStereotype * st = UmlSettings::_map_relation_attribute_stereotypes.value(s);

        if (st == 0)
            st = UmlSettings::add_rel_attr_stereotype(s);

        st->idl = v;

        return TRUE;
    }
    else
        return FALSE;
}

QByteArray IdlSettings::relationAttributeUmlStereotype(QByteArray s)
{
    read_if_needed_();

    return UmlSettings::uml_rel_attr_stereotype(s, &UmlStereotype::idl);
}

QByteArray IdlSettings::classStereotype(QByteArray s)
{
    read_if_needed_();

    UmlStereotype * b = UmlSettings::_map_class_stereotypes.value(s);

    return (b) ? b->idl : "valuetype";
}

bool IdlSettings::set_ClassStereotype(QByteArray s, QByteArray v)
{
    read_if_needed_();
    UmlCom::send_cmd(idlSettingsCmd, setIdlClassStereotypeCmd, (const char *)s, (const char *)v); //[rageek] Fix prototype

    if (UmlCom::read_bool()) {
        UmlStereotype * st = UmlSettings::_map_class_stereotypes.value(s);

        if (st == 0)
            st = UmlSettings::add_class_stereotype(s);

        st->idl = v;

        return TRUE;
    }
    else
        return FALSE;
}

QByteArray IdlSettings::classUmlStereotype(QByteArray s)
{
    read_if_needed_();

    return UmlSettings::uml_class_stereotype(s, &UmlStereotype::idl);
}

QByteArray IdlSettings::include(QByteArray s)
{
    read_if_needed_();

    QByteArray * r = _map_includes[s];

    return (r) ? *r : QByteArray(0);
}

bool IdlSettings::set_Include(QByteArray s, QByteArray v)
{
    read_if_needed_();
    UmlCom::send_cmd(idlSettingsCmd, setIdlIncludeCmd, (const char *)s, (const char *)v); //[rageek] Fix prototype

    if (UmlCom::read_bool()) {
        QByteArray * r = _map_includes.take(s);

        if (!v.isEmpty())
            _map_includes.insert(s, new QByteArray(v));

        if (r)
            delete r;

        return TRUE;
    }
    else
        return FALSE;
}

const QByteArray & IdlSettings::rootDir()
{
    read_if_needed_();

    return _root;
}

bool IdlSettings::set_RootDir(QByteArray v)
{
    UmlCom::send_cmd(idlSettingsCmd, setIdlRootDirCmd, (const char *)v); //[rageek] Fix prototype

    if (UmlCom::read_bool()) {
        _root = v;
        return TRUE;
    }
    else
        return FALSE;
}

const QByteArray & IdlSettings::sourceContent()
{
    read_if_needed_();

    return _src_content;
}

bool IdlSettings::set_SourceContent(QByteArray v)
{
    UmlCom::send_cmd(idlSettingsCmd, setIdlSourceContentCmd, (const char *)v); //[rageek] Fix prototype

    if (UmlCom::read_bool()) {
        _src_content = v;
        return TRUE;
    }
    else
        return FALSE;
}

const QByteArray & IdlSettings::sourceExtension()
{
    read_if_needed_();

    return _ext;
}

bool IdlSettings::set_SourceExtension(QByteArray v)
{
    UmlCom::send_cmd(idlSettingsCmd, setIdlSourceExtensionCmd, (const char *)v); //[rageek] Fix prototype

    if (UmlCom::read_bool()) {
        _ext = v;
        return TRUE;
    }
    else
        return FALSE;
}

const QByteArray & IdlSettings::interfaceDecl()
{
    read_if_needed_();

    return _interface_decl;
}

bool IdlSettings::set_InterfaceDecl(QByteArray v)
{
    UmlCom::send_cmd(idlSettingsCmd, setIdlInterfaceDeclCmd, (const char *)v); //[rageek] Fix prototype

    if (UmlCom::read_bool()) {
        _interface_decl = v;
        return TRUE;
    }
    else
        return FALSE;
}

const QByteArray & IdlSettings::valuetypeDecl()
{
    read_if_needed_();

    return _valuetype_decl;
}

bool IdlSettings::set_ValuetypeDecl(QByteArray v)
{
    UmlCom::send_cmd(idlSettingsCmd, setIdlValuetypeDeclCmd, (const char *)v); //[rageek] Fix prototype

    if (UmlCom::read_bool()) {
        _valuetype_decl = v;
        return TRUE;
    }
    else
        return FALSE;
}

const QByteArray & IdlSettings::externalClassDecl()
{
    read_if_needed_();

    return _external_class_decl;
}

bool IdlSettings::set_ExternalClassDecl(QByteArray v)
{
    UmlCom::send_cmd(idlSettingsCmd, setIdlExternalClassDeclCmd, (const char *)v); //[rageek] Fix prototype

    if (UmlCom::read_bool()) {
        _external_class_decl = v;
        return TRUE;
    }
    else
        return FALSE;
}

const QByteArray & IdlSettings::structDecl()
{
    read_if_needed_();

    return _struct_decl;
}

bool IdlSettings::set_StructDecl(QByteArray v)
{
    UmlCom::send_cmd(idlSettingsCmd, setIdlStructDeclCmd, (const char *)v); //[rageek] Fix prototype

    if (UmlCom::read_bool()) {
        _struct_decl = v;
        return TRUE;
    }
    else
        return FALSE;
}

const QByteArray & IdlSettings::typedefDecl()
{
    read_if_needed_();

    return _typedef_decl;
}

bool IdlSettings::set_TypedefDecl(QByteArray v)
{
    UmlCom::send_cmd(idlSettingsCmd, setIdlTypedefDeclCmd, (const char *)v); //[rageek] Fix prototype

    if (UmlCom::read_bool()) {
        _typedef_decl = v;
        return TRUE;
    }
    else
        return FALSE;
}

const QByteArray & IdlSettings::exceptionDecl()
{
    read_if_needed_();

    return _exception_decl;
}

bool IdlSettings::set_ExceptionDecl(QByteArray v)
{
    UmlCom::send_cmd(idlSettingsCmd, setIdlExceptionDeclCmd, (const char *)v); //[rageek] Fix prototype

    if (UmlCom::read_bool()) {
        _exception_decl = v;
        return TRUE;
    }
    else
        return FALSE;
}

const QByteArray & IdlSettings::unionDecl()
{
    read_if_needed_();

    return _union_decl;
}

bool IdlSettings::set_UnionDecl(QByteArray v)
{
    UmlCom::send_cmd(idlSettingsCmd, setIdlUnionDeclCmd, (const char *)v); //[rageek] Fix prototype

    if (UmlCom::read_bool()) {
        _union_decl = v;
        return TRUE;
    }
    else
        return FALSE;
}

const QByteArray & IdlSettings::enumDecl()
{
    read_if_needed_();

    return _enum_decl;
}

bool IdlSettings::set_EnumDecl(QByteArray v)
{
    UmlCom::send_cmd(idlSettingsCmd, setIdlEnumDeclCmd, (const char *)v); //[rageek] Fix prototype

    if (UmlCom::read_bool()) {
        _enum_decl = v;
        return TRUE;
    }
    else
        return FALSE;
}

const QByteArray & IdlSettings::attributeDecl(const char * multiplicity)
{
    read_if_needed_();

    return _attr_decl[UmlSettings::multiplicity_column(multiplicity)];
}

bool IdlSettings::set_AttributeDecl(const char * multiplicity, QByteArray v)
{
    read_if_needed_();
    UmlCom::send_cmd(idlSettingsCmd, setIdlAttributeDeclCmd, multiplicity, (const char *)v); //[rageek] Fix prototype

    if (UmlCom::read_bool()) {
        _attr_decl[UmlSettings::multiplicity_column(multiplicity)] = v;
        return TRUE;
    }
    else
        return FALSE;
}

const QByteArray & IdlSettings::valuetypeAttributeDecl(const char * multiplicity)
{
    read_if_needed_();

    return _valuetype_attr_decl[UmlSettings::multiplicity_column(multiplicity)];
}

bool IdlSettings::set_ValuetypeAttributeDecl(const char * multiplicity, QByteArray v)
{
    read_if_needed_();
    UmlCom::send_cmd(idlSettingsCmd, setIdlValuetypeAttributeDeclCmd, multiplicity, (const char *)v); //[rageek] Fix prototype

    if (UmlCom::read_bool()) {
        _valuetype_attr_decl[UmlSettings::multiplicity_column(multiplicity)] = v;
        return TRUE;
    }
    else
        return FALSE;
}

const QByteArray & IdlSettings::unionItemDecl(const char * multiplicity)
{
    read_if_needed_();

    return _union_item_decl[UmlSettings::multiplicity_column(multiplicity)];
}

bool IdlSettings::set_UnionItemDecl(const char * multiplicity, QByteArray v)
{
    read_if_needed_();
    UmlCom::send_cmd(idlSettingsCmd, setIdlUnionItemDeclCmd, multiplicity, (const char *)v); //[rageek] Fix prototype

    if (UmlCom::read_bool()) {
        _union_item_decl[UmlSettings::multiplicity_column(multiplicity)] = v;
        return TRUE;
    }
    else
        return FALSE;
}

const QByteArray & IdlSettings::enumItemDecl()
{
    read_if_needed_();

    return _enum_item_decl;
}

bool IdlSettings::set_EnumItemDecl(QByteArray v)
{
    UmlCom::send_cmd(idlSettingsCmd, setIdlEnumItemDeclCmd, (const char *)v); //[rageek] Fix prototype

    if (UmlCom::read_bool()) {
        _enum_item_decl = v;
        return TRUE;
    }
    else
        return FALSE;
}

const QByteArray & IdlSettings::constDecl(const char * multiplicity)
{
    read_if_needed_();

    return _const_decl[UmlSettings::multiplicity_column(multiplicity)];
}

bool IdlSettings::set_ConstDecl(const char * multiplicity, QByteArray v)
{
    read_if_needed_();
    UmlCom::send_cmd(idlSettingsCmd, setIdlConstDeclCmd, multiplicity, (const char *)v); //[rageek] Fix prototype

    if (UmlCom::read_bool()) {
        _const_decl[UmlSettings::multiplicity_column(multiplicity)] = v;
        return TRUE;
    }
    else
        return FALSE;
}

const QByteArray & IdlSettings::relationDecl(const char * multiplicity)
{
    read_if_needed_();

    return _rel_decl[UmlSettings::multiplicity_column(multiplicity)];
}

bool IdlSettings::set_RelationDecl(const char * multiplicity, QByteArray v)
{
    read_if_needed_();
    UmlCom::send_cmd(idlSettingsCmd, setIdlRelationDeclCmd, multiplicity, (const char *)v); //[rageek] Fix prototype

    if (UmlCom::read_bool()) {
        _rel_decl[UmlSettings::multiplicity_column(multiplicity)] = v;
        return TRUE;
    }
    else
        return FALSE;
}

const QByteArray & IdlSettings::valuetypeRelationDecl(const char * multiplicity)
{
    read_if_needed_();

    return _valuetype_rel_decl[UmlSettings::multiplicity_column(multiplicity)];
}

bool IdlSettings::set_ValuetypeRelationDecl(const char * multiplicity, QByteArray v)
{
    read_if_needed_();
    UmlCom::send_cmd(idlSettingsCmd, setIdlValuetypeRelationDeclCmd, multiplicity, (const char *)v); //[rageek] Fix prototype

    if (UmlCom::read_bool()) {
        _valuetype_rel_decl[UmlSettings::multiplicity_column(multiplicity)] = v;
        return TRUE;
    }
    else
        return FALSE;
}

const QByteArray & IdlSettings::unionRelationDecl(const char * multiplicity)
{
    read_if_needed_();

    return _union_rel_decl[UmlSettings::multiplicity_column(multiplicity)];
}

bool IdlSettings::set_UnionRelationDecl(const char * multiplicity, QByteArray v)
{
    read_if_needed_();
    UmlCom::send_cmd(idlSettingsCmd, setIdlUnionRelationDeclCmd, multiplicity, (const char *)v); //[rageek] Fix prototype

    if (UmlCom::read_bool()) {
        _union_rel_decl[UmlSettings::multiplicity_column(multiplicity)] = v;
        return TRUE;
    }
    else
        return FALSE;
}

const QByteArray & IdlSettings::operationDecl()
{
    read_if_needed_();

    return _oper_decl;
}

bool IdlSettings::set_OperationDecl(QByteArray v)
{
    UmlCom::send_cmd(idlSettingsCmd, setIdlOperationDeclCmd, (const char *)v); //[rageek] Fix prototype

    if (UmlCom::read_bool()) {
        _oper_decl = v;
        return TRUE;
    }
    else
        return FALSE;
}

const QByteArray & IdlSettings::getName()
{
    read_if_needed_();

    return _get_name;
}

bool IdlSettings::set_GetName(QByteArray v)
{
    UmlCom::send_cmd(idlSettingsCmd, setIdlGetNameCmd, (const char *)v); //[rageek] Fix prototype

    if (UmlCom::read_bool()) {
        _get_name = v;
        return TRUE;
    }
    else
        return FALSE;
}

const QByteArray & IdlSettings::setName()
{
    read_if_needed_();

    return _set_name;
}

bool IdlSettings::set_SetName(QByteArray v)
{
    UmlCom::send_cmd(idlSettingsCmd, setIdlSetNameCmd, (const char *)v); //[rageek] Fix prototype

    if (UmlCom::read_bool()) {
        _set_name = v;
        return TRUE;
    }
    else
        return FALSE;
}

bool IdlSettings::isSetOneway()
{
    read_if_needed_();

    return _is_set_oneway;
}

bool IdlSettings::set_IsSetOneway(bool v)
{
    UmlCom::send_cmd(idlSettingsCmd, setIdlIsSetOneWayCmd, v);

    if (UmlCom::read_bool()) {
        _is_set_oneway = v;
        return TRUE;
    }
    else
        return FALSE;
}

bool IdlSettings::_defined;

QByteArray IdlSettings::_root;

QByteArray IdlSettings::_interface_decl;

QByteArray IdlSettings::_valuetype_decl;

QByteArray IdlSettings::_struct_decl;

QByteArray IdlSettings::_typedef_decl;

QByteArray IdlSettings::_exception_decl;

QByteArray IdlSettings::_union_decl;

QByteArray IdlSettings::_enum_decl;

QByteArray IdlSettings::_external_class_decl;

QByteArray IdlSettings::_attr_decl[3/*multiplicity*/];

QByteArray IdlSettings::_valuetype_attr_decl[3/*multiplicity*/];

QByteArray IdlSettings::_union_item_decl[3/*multiplicity*/];

QByteArray IdlSettings::_enum_item_decl;

QByteArray IdlSettings::_const_decl[3/*multiplicity*/];

QByteArray IdlSettings::_rel_decl[3/*multiplicity*/];

QByteArray IdlSettings::_valuetype_rel_decl[3/*multiplicity*/];

QByteArray IdlSettings::_union_rel_decl[3/*multiplicity*/];

QByteArray IdlSettings::_oper_decl;

QByteArray IdlSettings::_get_name;

QByteArray IdlSettings::_set_name;

bool IdlSettings::_is_set_oneway;

QByteArray IdlSettings::_src_content;

QByteArray IdlSettings::_ext;

QHash<QByteArray,QByteArray*> IdlSettings::_map_includes;

void IdlSettings::read_()
{
    _root = UmlCom::read_string();

    unsigned n;
    unsigned index;

    n = UmlCom::read_unsigned();

    for (index = 0; index != n; index += 1) {
        UmlSettings::_builtins[index].idl = UmlCom::read_string();
    }

    n = UmlCom::read_unsigned();

    for (index = 0; index != n; index += 1)
        UmlSettings::_relation_attribute_stereotypes[index].idl = UmlCom::read_string();

    n = UmlCom::read_unsigned();

    for (index = 0; index != n; index += 1)
        UmlSettings::_class_stereotypes[index].idl = UmlCom::read_string();

    n = UmlCom::read_unsigned();
    _map_includes.clear();

    if (n > _map_includes.size())
        _map_includes.reserve(n);

    for (index = 0; index != n; index += 1) {
        QByteArray t = UmlCom::read_string();
        QByteArray i = UmlCom::read_string();

        _map_includes.insert(t, new QByteArray(i));
    }

    _src_content = UmlCom::read_string();
    _ext = UmlCom::read_string();

    _interface_decl = UmlCom::read_string();
    _valuetype_decl = UmlCom::read_string();
    _struct_decl = UmlCom::read_string();
    _typedef_decl = UmlCom::read_string();
    _exception_decl = UmlCom::read_string();
    _union_decl = UmlCom::read_string();
    _enum_decl = UmlCom::read_string();
    _external_class_decl = UmlCom::read_string();

    _enum_item_decl = UmlCom::read_string();

    for (index = 0; index != 3; index += 1) {
        _attr_decl[index] = UmlCom::read_string();
        _valuetype_attr_decl[index] = UmlCom::read_string();
        _union_item_decl[index] = UmlCom::read_string();
        _const_decl[index] = UmlCom::read_string();
        _rel_decl[index] = UmlCom::read_string();
        _valuetype_rel_decl[index] = UmlCom::read_string();
        _union_rel_decl[index] = UmlCom::read_string();
    }

    _oper_decl = UmlCom::read_string();
    _get_name = UmlCom::read_string();
    _set_name = UmlCom::read_string();
    _is_set_oneway = UmlCom::read_bool();
}

void IdlSettings::read_if_needed_()
{
    UmlSettings::read_if_needed_();

    if (!_defined) {
        UmlCom::send_cmd(idlSettingsCmd, getIdlSettingsCmd);
        read_();
        _defined = TRUE;
    }
}


#endif
