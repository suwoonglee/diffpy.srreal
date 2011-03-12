/*****************************************************************************
*
* diffpy.srreal     by DANSE Diffraction group
*                   Simon J. L. Billinge
*                   (c) 2011 Trustees of the Columbia University
*                   in the City of New York.  All rights reserved.
*
* File coded by:    Pavol Juhas
*
* See AUTHORS.txt for a list of people who contributed.
* See LICENSE.txt for license information.
*
******************************************************************************
*
* Bindings to the BVParametersTable and BVParam classes.
*
* $Id$
*
*****************************************************************************/

#include <string>
#include <boost/python.hpp>
#include <diffpy/srreal/BVParam.hpp>
#include <diffpy/srreal/BVParametersTable.hpp>
#include "srreal_converters.hpp"
#include "srreal_pickling.hpp"

namespace srrealmodule {
namespace nswrap_BVParametersTable {

using namespace boost::python;
using namespace diffpy::srreal;

// docstrings ----------------------------------------------------------------

const char* doc_BVParam = "\
Storage of bond valence parameters for a given cation-anion pair.\n\
";

const char* doc_BVParam___init__ = "\
Initialize new instance of the BVParam class.\n\
\n\
atom0    -- symbol of the cation atom, no charge specification\n\
valence0 -- integer cation valence, must be positive\n\
atom0    -- symbol of the anion atom, no charge specification\n\
valence0 -- integer anion valence, must be negative\n\
Ro       -- valence parameter Ro\n\
B        -- valence parameter B\n\
ref_id   -- code of the reference paper in bvparm2009.cif (optional)\n\
";

const char* doc_BVParam___repr__ = "\
String representation of the BVParam object\n\
";

const char* doc_BVParam_bondvalence = "\
Bond valence of the specified distance in Angstroms.\n\
";

const char* doc_BVParam_bondvalenceToDistance = "\
Distance in Angstroms corresponding to specified bond valence.\n\
";

const char* doc_BVParam_setFromCifLine = "\
Update bond valence data from a string formatted as in bvparm2009.cif.\n\
";

const char* doc_BVParam_atom0 = "\
Bare symbol of the cation atom without charge specification.\n\
";

const char* doc_BVParam_valence0 = "\
Positive integer valence of the cation.\n\
";

const char* doc_BVParam_atom1 = "\
Bare symbol of the anion atom without charge specification.\n\
";

const char* doc_BVParam_valence1 = "\
Negative integer valence of the anion.\n\
";

const char* doc_BVParam_Ro = "\
Bond valence parameter Ro in Angstroms.\n\
";

const char* doc_BVParam_B = "\
Bond valence parameter B in Angstroms.\n\
";

const char* doc_BVParam_ref_id = "\
code of the reference paper in bvparm2009.cif.\n\
";

const char* doc_BVParametersTable = "FIXME";
const char* doc_BVParametersTable_none = "FIXME";
const char* doc_BVParametersTable_lookup = "FIXME";
const char* doc_BVParametersTable_setCustom = "FIXME";
const char* doc_BVParametersTable_resetCustom = "FIXME";
const char* doc_BVParametersTable_resetAll = "FIXME";
const char* doc_BVParametersTable_getAll = "FIXME";

// wrappers ------------------------------------------------------------------

BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(setcustom6, setCustom, 6, 7)
DECLARE_PYSET_METHOD_WRAPPER(getAll, getAll_asset)

object repr_BVParam(const BVParam& bp)
{
    object rv = ("BVParam(%r, %i, %r, %i, Ro=%s, B=%s, ref_id=%r)" %
        make_tuple(bp.matom0, bp.mvalence0, bp.matom1, bp.mvalence1,
            bp.mRo, bp.mB, bp.mref_id));
    return rv;
}


object singleton_none()
{
    static object rv(BVParametersTable::none());
    return rv;
}

}   // namespace nswrap_BVParametersTable

// Wrapper definition --------------------------------------------------------

void wrap_BVParametersTable()
{
    using namespace nswrap_BVParametersTable;
    using std::string;

    class_<BVParam>("BVParam", doc_BVParam)
        .def(init<const string&, int, const string&, int,
                double, double, string>(doc_BVParam___init__,
                    (arg("atom0"), arg("valence0"),
                    arg("atom1"), arg("valence1"), arg("Ro")=0.0, arg("B")=0.0,
                    arg("ref_id")="")))
        .def("__repr__", repr_BVParam, doc_BVParam___repr__)
        .def(self == self)
        .def("bondvalence", &BVParam::bondvalence,
                arg("distance"), doc_BVParam_bondvalence)
        .def("bondvalenceToDistance", &BVParam::bondvalenceToDistance,
                arg("valence"), doc_BVParam_bondvalenceToDistance)
        .def("setFromCifLine", &BVParam::setFromCifLine,
                doc_BVParam_setFromCifLine)
        .def_readonly("atom0", &BVParam::matom0, doc_BVParam_atom0)
        .def_readonly("valence0", &BVParam::mvalence0, doc_BVParam_valence0)
        .def_readonly("atom1", &BVParam::matom1, doc_BVParam_atom1)
        .def_readonly("valence1", &BVParam::mvalence1, doc_BVParam_valence1)
        .def_readwrite("Ro", &BVParam::mRo, doc_BVParam_Ro)
        .def_readwrite("B", &BVParam::mB, doc_BVParam_B)
        .def_readwrite("ref_id", &BVParam::mref_id, doc_BVParam_ref_id)
        .def_pickle(SerializationPickleSuite<BVParam>())
        ;

    typedef const BVParam&(BVParametersTable::*bptb_bvparam_1)(
            const BVParam&) const;
    typedef const BVParam&(BVParametersTable::*bptb_bvparam_4)(
            const string&, int, const string&, int) const;
    typedef void(BVParametersTable::*bptb_void_1)(
            const BVParam&);
    typedef void(BVParametersTable::*bptb_void_4)(
            const string&, int, const string&, int);

    class_<BVParametersTable>("BVParametersTable", doc_BVParametersTable)
        .def("none", singleton_none, doc_BVParametersTable_none)
        .staticmethod("none")
        .def("lookup", bptb_bvparam_1(&BVParametersTable::lookup),
                doc_BVParametersTable_lookup,
                return_value_policy<copy_const_reference>())
        .def("lookup", bptb_bvparam_4(&BVParametersTable::lookup),
                doc_BVParametersTable_lookup,
                return_value_policy<copy_const_reference>())
        .def("setCustom", bptb_void_1(&BVParametersTable::setCustom),
                doc_BVParametersTable_setCustom)
        .def("setCustom", (void(BVParametersTable::*)(const string&, int,
                    const string&, int, double, double, string)) NULL,
                setcustom6(doc_BVParametersTable_setCustom))
        .def("resetCustom", bptb_void_1(&BVParametersTable::resetCustom),
                doc_BVParametersTable_resetCustom)
        .def("resetCustom", bptb_void_4(&BVParametersTable::resetCustom),
                doc_BVParametersTable_resetCustom)
        .def("resetAll", &BVParametersTable::resetAll,
                doc_BVParametersTable_resetCustom)
        .def("getAll", getAll_asset<BVParametersTable>,
                doc_BVParametersTable_getAll)
        .def_pickle(SerializationPickleSuite<BVParametersTable>())
        ;

    register_ptr_to_python<BVParametersTablePtr>();
}

}   // namespace srrealmodule

// End of file