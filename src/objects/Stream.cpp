#include "Stream.hpp"

const std::vector<uint8_t> charta::pdf::Stream::calculateFilteredData()
{
    switch (m_filter)
    {
    case Filter::None:
        return m_data;

    default:
        break;
    }
}
