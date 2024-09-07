/*******************************************************************************
 * @Author : yongheng
 * @Data   : 2024/09/07 13:02
*******************************************************************************/


#pragma once

#include <chrono>


class Time {
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
    Time();
    explicit Time(std::chrono::system_clock::time_point);
    size_t count(const CountType) const ;

	size_t millisecond() const ;
	size_t second() const ;
	size_t minute() const ;
	size_t hour() const ;
	size_t day() const ;
	size_t mouth() const ;
	size_t year() const ;
	bool is_leap() const ;

};
