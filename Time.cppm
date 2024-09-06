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
	explicit Date(const std::chrono::system_clock::time_point time_point) {
		time_point_ = std::chrono::current_zone()->to_local(time_point);
		ymd_ = std::chrono::year_month_day(floor<std::chrono::days>(time_point_));
	}

    size_t count(const CountType type = CountType::Nanosecond) const {
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
	size_t millisecond() const {
		return count(CountType::Millisecond) % 1000;
	}
	size_t second() const {
		return count(CountType::Second) % 60;
	}
	size_t minute() const {
		return count(CountType::Minute) % 60;
	}
	size_t hour() const {
		return count(CountType::Hour) % 24;
	}
	size_t day() const {
		return ymd_.day().operator unsigned int();
	}
	size_t mouth() const {
		return ymd_.month().operator unsigned int();
	}
	size_t year() const {
		return ymd_.year().operator int();
	}
	bool is_leap() const {
		return ymd_.year().is_leap();
	}
};
