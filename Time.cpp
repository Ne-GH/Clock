/*******************************************************************************
 * @Author : yongheng
 * @Data   : 2024/09/07 13:02
*******************************************************************************/


#include "Time.h"

Time::Time() : Time(std::chrono::system_clock::now()) {  }
Time::Time(const std::chrono::system_clock::time_point time_point) {
    time_point_ = std::chrono::current_zone()->to_local(time_point);
    ymd_ = std::chrono::year_month_day(floor<std::chrono::days>(time_point_));
}

size_t Time::count(const CountType type = CountType::Nanosecond) const {
    switch (type) {
    case CountType::Nanosecond:
        return std::chrono::duration_cast<std::chrono::nanoseconds>(time_point_.time_since_epoch()).count();
    case CountType::Microsecond:
        return std::chrono::duration_cast<std::chrono::microseconds>(time_point_.time_since_epoch()).count();
    case CountType::Millisecond:
        return std::chrono::duration_cast<std::chrono::milliseconds> (time_point_.time_since_epoch()).count();
    case CountType::Second:
        return std::chrono::duration_cast<std::chrono::seconds> (time_point_.time_since_epoch()).count();
    case CountType::Minute:
        return std::chrono::duration_cast<std::chrono::minutes> (time_point_.time_since_epoch()).count();
    case CountType::Hour:
        return std::chrono::duration_cast<std::chrono::hours> (time_point_.time_since_epoch()).count();
    case CountType::Day:
        return std::chrono::duration_cast<std::chrono::days> (time_point_.time_since_epoch()).count();
    case CountType::Week:
        return std::chrono::duration_cast<std::chrono::weeks> (time_point_.time_since_epoch()).count();
    case CountType::Year:
        return std::chrono::duration_cast<std::chrono::years> (time_point_.time_since_epoch()).count();
    default:
        return -1;
    }
}

size_t Time::millisecond() const {
    return count(CountType::Millisecond) % 1000;
}
size_t Time::second() const {
    return count(CountType::Second) % 60;
}
size_t Time::minute() const {
    return count(CountType::Minute) % 60;
}
size_t Time::hour() const {
    return count(CountType::Hour) % 24;
}
size_t Time::day() const {
    return ymd_.day().operator unsigned int();
}
size_t Time::mouth() const {
    return ymd_.month().operator unsigned int();
}
size_t Time::year() const {
    return ymd_.year().operator int();
}
bool Time::is_leap() const {
    return ymd_.year().is_leap();
}
