#include <benchmark/benchmark.h>
#include <charta/Document.hpp>
#include <sstream>

using namespace charta::pdf;

static void BM_EmptyDocument(benchmark::State &state)
{
    for (auto _ : state)
    {
        std::stringstream ss;
        Document doc;

        doc.saveToStream(ss);
    }
}
// Register the function as a benchmark
BENCHMARK(BM_EmptyDocument);

static void BM_PagesDocument(benchmark::State &state)
{
    for (auto _ : state)
    {
        std::stringstream ss;
        Document doc;

        Page first;
        doc.addPage(first);

        doc.saveToStream(ss);
    }
}
// Register the function as a benchmark
BENCHMARK(BM_PagesDocument);