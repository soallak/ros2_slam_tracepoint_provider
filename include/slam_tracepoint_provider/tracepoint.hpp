#undef LTTNG_UST_TRACEPOINT_PROVIDER
#define LTTNG_UST_TRACEPOINT_PROVIDER slam_tracepoint_provider

#undef LTTNG_UST_TRACEPOINT_INCLUDE
#define LTTNG_UST_TRACEPOINT_INCLUDE "slam_tracepoint_provider/tracepoint.hpp"

#if !defined(_TP_H) || defined(LTTNG_UST_TRACEPOINT_HEADER_MULTI_READ)
#define _TP_H

#include <lttng/tracepoint.h>

#include <chrono>
#include <rclcpp/rclcpp.hpp>
#include <string>

/* ros2 callback tracepoints */

LTTNG_UST_TRACEPOINT_EVENT_CLASS(
    LTTNG_UST_TRACEPOINT_PROVIDER,

    ros2_callback_class,

    LTTNG_UST_TP_ARGS(std::shared_ptr<rclcpp::Node>, node, rclcpp::Time const&,
                      timepoint, std::string, label),

    LTTNG_UST_TP_FIELDS(
        lttng_ust_field_string(node_name, node ? node->get_name() : "")
            lttng_ust_field_float(double, stamp, timepoint.seconds())
                lttng_ust_field_string(label, label.c_str()))

)

LTTNG_UST_TRACEPOINT_EVENT_INSTANCE(

    LTTNG_UST_TRACEPOINT_PROVIDER,

    ros2_callback_class,

    LTTNG_UST_TRACEPOINT_PROVIDER,

    ros2_callback_enter,

    LTTNG_UST_TP_ARGS(std::shared_ptr<rclcpp::Node>, node, rclcpp::Time const&,
                      timepoint, std::string, label)

)

LTTNG_UST_TRACEPOINT_EVENT_INSTANCE(

    LTTNG_UST_TRACEPOINT_PROVIDER,

    ros2_callback_class,

    LTTNG_UST_TRACEPOINT_PROVIDER,

    ros2_callback_exit,

    LTTNG_UST_TP_ARGS(std::shared_ptr<rclcpp::Node>, node, rclcpp::Time const&,
                      timepoint, std::string, label)

)

LTTNG_UST_TRACEPOINT_LOGLEVEL(LTTNG_UST_TRACEPOINT_PROVIDER,
                              ros2_callback_enter,
                              LTTNG_UST_TRACEPOINT_LOGLEVEL_DEBUG)

LTTNG_UST_TRACEPOINT_LOGLEVEL(LTTNG_UST_TRACEPOINT_PROVIDER, ros2_callback_exit,
                              LTTNG_UST_TRACEPOINT_LOGLEVEL_DEBUG)

/* compute trace points */

LTTNG_UST_TRACEPOINT_EVENT_CLASS(
    LTTNG_UST_TRACEPOINT_PROVIDER,

    compute_class,

    LTTNG_UST_TP_ARGS(std::shared_ptr<rclcpp::Node>, node,
                      std::chrono::nanoseconds const&, duration, std::string,
                      label),

    LTTNG_UST_TP_FIELDS(
        lttng_ust_field_string(node_name, node ? node->get_name() : "")
            lttng_ust_field_float(double, duration,
                                  static_cast<double>(duration.count()))
                lttng_ust_field_string(label, label.c_str()))

)

LTTNG_UST_TRACEPOINT_EVENT_INSTANCE(

    LTTNG_UST_TRACEPOINT_PROVIDER,

    compute_class,

    LTTNG_UST_TRACEPOINT_PROVIDER,

    compute_cpu,

    LTTNG_UST_TP_ARGS(std::shared_ptr<rclcpp::Node>, node,
                      std::chrono::nanoseconds const&, duration, std::string,
                      label)

)

LTTNG_UST_TRACEPOINT_EVENT_INSTANCE(

    LTTNG_UST_TRACEPOINT_PROVIDER,

    compute_class,

    LTTNG_UST_TRACEPOINT_PROVIDER,

    compute_fpga,
    LTTNG_UST_TP_ARGS(std::shared_ptr<rclcpp::Node>, node,
                      std::chrono::nanoseconds const&, duration, std::string,
                      label)

)

LTTNG_UST_TRACEPOINT_LOGLEVEL(LTTNG_UST_TRACEPOINT_PROVIDER, compute_cpu,
                              LTTNG_UST_TRACEPOINT_LOGLEVEL_INFO)

LTTNG_UST_TRACEPOINT_LOGLEVEL(LTTNG_UST_TRACEPOINT_PROVIDER, compute_fpga,
                              LTTNG_UST_TRACEPOINT_LOGLEVEL_INFO)

/* helper macros */

/**
 * @brief ROS2 Callback enter tracepoint
 *
 */
#define TP_CALLBACK_ENTER(node, time, label)                                \
  lttng_ust_tracepoint(slam_tracepoint_provider, ros2_callback_enter, node, \
                       time, label)
/**
 * @brief ROS2 Callback exit tracepoint
 *
 */
#define TP_CALLBACK_EXIT(node, time, label)                                \
  lttng_ust_tracepoint(slam_tracepoint_provider, ros2_callback_exit, node, \
                       time, label)

/**
 * @brief CPU Computation Tracepoint
 *
 */
#define TP_COMPUTE_CPU(node, duration, label)                                 \
  lttng_ust_tracepoint(slam_tracepoint_provider, compute_cpu, node, duration, \
                       label)

/**
 * @brief FPGA Computation Tracepoint
 *
 */
#define TP_COMPUTE_FPGA(node, duration, label)                                 \
  lttng_ust_tracepoint(slam_tracepoint_provider, compute_fpga, node, duration, \
                       label)

#endif /* _TP_H */

#include <lttng/tracepoint-event.h>
