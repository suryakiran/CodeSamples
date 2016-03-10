#include <iostream>
#include <Alembic/Abc/All.h>
#include <Alembic/AbcCoreOgawa/All.h>
#include <Alembic/AbcCoreHDF5/All.h>
#include <Alembic/AbcGeom/All.h>


int main (void)
{
    {
        std::cout << "Writing ogawa" << std::endl;
        Alembic::Abc::OArchive outArchive (Alembic::AbcCoreOgawa::WriteArchive(), "test-ogawa.abc");
    }
    {
        std::cout << "Writing hdf5" << std::endl;
        Alembic::Abc::OArchive outArchive (Alembic::AbcCoreHDF5::WriteArchive(), "test-hdf5.abc");
    }

    return 0;
}
