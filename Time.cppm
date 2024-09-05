module;
#include <chrono>
export module Date;

export 
class Date {
	std::chrono::local_time<std::chrono::system_clock::duration> time_point_;
	std::chrono::year_month_day ymd_{};

public:
	enum class CountType {
		Nanosecond,
		Microsecond,
		Millisecond,
		Second,
		Minute,
		Hour,
		Day,
		Week,
		Year
	};

	Date() : Date(std::chrono::system_clock::now()) {  }
	explicit Date(std::chrono::system_clock::time_point time_point) { 
		time_point_ = std::chrono::current_zone()->to_local(time_point);
		ymd_ = std::chrono::year_month_day(floor<std::chrono::days>(time_point_));
	}

    size_t count(CountType type = CountType::Nanosecond) {
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
	size_t millisecond() {
		return count(CountType::Millisecond) % 1000;
	}
	size_t second() {
		return count(CountType::Second) % 60;
	}
	size_t minute() {
		return count(CountType::Minute) % 60;
	}
	size_t hour() {
		return count(CountType::Hour) % 24;
	}
	size_t day() {
		return ymd_.day().operator unsigned int();
	}
	size_t mouth() {
		return ymd_.month().operator unsigned int();
	}
	size_t year() {
		return ymd_.year().operator int();
	}
	bool is_leap() {
		return ymd_.year().is_leap();
	}
};
