#!/usr/bin/env python

# Installation script for diffpy.Structure

"""diffpy.srreal - prototype for new PDF calculator and assortment
of real space utilities.

Packages:   diffpy.srreal
Scripts:    (none yet)
"""

from setuptools import setup, find_packages
from setuptools import Extension
import fix_setuptools_chmod

# define extensions here
ext_objects = ['srrealmodule/srreal_converters.cpp']
ext_kws = {
        'libraries' : ['diffpy'],
        'undef_macros' : ['NDEBUG'],
        'extra_compile_args' : [],
        'extra_link_args' : [],
}
srrealmodules = [
    Extension('diffpy.srreal.pdf_ext',
        ['srrealmodule/pdf_ext.cpp'] + ext_objects, **ext_kws),
    Extension('diffpy.srreal.bvs_ext',
        ['srrealmodule/bvs_ext.cpp'] + ext_objects, **ext_kws),
]

# define distribution
dist = setup(
        name = "diffpy.srreal",
        version = "0.2a1",
        namespace_packages = ['diffpy'],
        packages = find_packages(),
        ext_modules = srrealmodules,
        install_requires = [
            'diffpy.Structure',
        ],
        dependency_links = [
            # REMOVE dev.danse.us for a public release.
            'http://dev.danse.us/packages/',
            "http://www.diffpy.org/packages/",
        ],

        author = "Simon J.L. Billinge",
        author_email = "sb2896@columbia.edu",
        description = "Prototype for new PDF calculator and other real " + \
                      "space utilities.",
        license = "BSD",
        url = "http://www.diffpy.org/",
        keywords = "PDF calculator real-space utilities",
)

# End of file