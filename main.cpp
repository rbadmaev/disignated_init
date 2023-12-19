#include <boost/operators.hpp>

#include <iostream>
#include <optional>
#include <set>
#include <algorithm>
#include <vector>


using DimensionId = unsigned;

//======================================================================================================================
// Optional type
template <class T>
using Optional = std::optional<T>;

static constexpr auto& None = std::nullopt;

template <typename ValueType>
std::ostream& operator<<(std::ostream& stream, const Optional<ValueType>& opt)
{
    if (!opt)
        stream << "<Null optional>";
    else
        stream << *opt;

    return stream;
}

//======================================================================================================================
class CellRangeTracingCompilerSettings : public boost::equality_comparable<CellRangeTracingCompilerSettings> {
public:
    CellRangeTracingCompilerSettings(unsigned a, unsigned b)
        : _tracedCubeIds{a, b}
    {
    }

    bool isCubeTraced(unsigned cubeId) const;
    unsigned mainTracedCubeId() const;
    bool operator==(const CellRangeTracingCompilerSettings& other) const;
    auto size() const
    {
        return _tracedCubeIds.size();
    }

private:
    std::vector<unsigned> _tracedCubeIds;
};

//----------------------------------------------------------------------------------------------------------------------
bool CellRangeTracingCompilerSettings::isCubeTraced(unsigned cubeId) const
{
    return std::find(_tracedCubeIds.begin(), _tracedCubeIds.end(), cubeId) != _tracedCubeIds.end();
}

//----------------------------------------------------------------------------------------------------------------------
unsigned CellRangeTracingCompilerSettings::mainTracedCubeId() const
{
    return _tracedCubeIds.front();
}

//----------------------------------------------------------------------------------------------------------------------
bool CellRangeTracingCompilerSettings::operator==(const CellRangeTracingCompilerSettings& other) const
{
    return _tracedCubeIds == other._tracedCubeIds;
}

//----------------------------------------------------------------------------------------------------------------------
std::ostream& operator<<(std::ostream& stream, const CellRangeTracingCompilerSettings& l)
{
    stream << &l << "{size=" << l.size() << "}";
    return stream;
}

//======================================================================================================================
struct CompilerSettings : public boost::equality_comparable<CompilerSettings> {
    bool allowSelfLinks = false;
    Optional<CellRangeTracingCompilerSettings> cellRangeTracing;
};

std::ostream& operator<<(std::ostream& stream, const CompilerSettings& l)
{
    stream << &l << "{"
           << "allowSelfLinks=" << l.allowSelfLinks
           << ", cellRangeTracing=" << l.cellRangeTracing
           << "}";
    return stream;
}

//======================================================================================================================
struct CompileFormulaArgs {
    int* cubeData = nullptr;
    CompilerSettings compilerSettings;
    bool updateCubesToRead = true;
};

std::ostream& operator<<(std::ostream& stream, const CompileFormulaArgs& l)
{
    stream << &l << "{cubeData=" << l.cubeData
           << ", compilerSettings=" << l.compilerSettings
           << ", updateCubesToRead=" << l.updateCubesToRead
           << "}";
    return stream;
}

void foo(const CompileFormulaArgs& l)
{
    std::cout << "foo: " << l << std::endl;
}

int main(int argc, char const* argv[])
{
    int i;
    std::cout << "&i" << &i << std::endl;
    foo({.cubeData = &i,
         .updateCubesToRead = false});
    return 0;
}
