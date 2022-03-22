#undef LTTNG_UST_TRACEPOINT_PROVIDER
#define LTTNG_UST_TRACEPOINT_PROVIDER slam_tracepoint_provider

#undef LTTNG_UST_TRACEPOINT_INCLUDE
#define LTTNG_UST_TRACEPOINT_INCLUDE "./tracepoint.h"

#if !defined(_TP_H) || defined(LTTNG_UST_TRACEPOINT_HEADER_MULTI_READ)
#define _TP_H

#include <lttng/tracepoint.h>

#include <rclcpp/rclcpp.hpp>

/* ros2 callback tracepoints */

LTTNG_UST_TRACEPOINT_EVENT_CLASS(
    LTTNG_UST_TRACEPOINT_PROVIDER,

    ros2_callback_class,

    LTTNG_UST_TP_ARGS(std::shared_ptr<rclcpp::Node>&, node, rclcpp::Time const&,
                      timepoint, char const*, label),

    LTTNG_UST_TP_FIELDS(lttng_ust_field_string(node_name, node->get_name())
                            lttng_ust_field_float(stamp, timepoint.seconds())
                                lttng_ust_field_string(label, label))

)

LTTNG_UST_TRACEPOINT_EVENT_INSTANCE(

    LTTNG_UST_TRACEPOINT_PROVIDER,

    ros2_callback_class,

    LTTNG_UST_TRACEPOINT_PROVIDER,

    ros2_callback_enter,

    LTTNG_UST_TP_ARGS(std::shared_ptr<rclcpp::Node>&, node, rclcpp::Time const&,
                      timepoint, char const*, label)

)

LTTNG_UST_TRACEPOINT_EVENT_INSTANCE(

    LTTNG_UST_TRACEPOINT_PROVIDER,

    ros2_callback_class,

    LTTNG_UST_TRACEPOINT_PROVIDER,

    ros2_callback_exit,

    LTTNG_UST_TP_ARGS(std::shared_ptr<rclcpp::Node>&, node, rclcpp::Time const&,
                      timepoint, char const*, label)

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

    LTTNG_UST_TP_ARGS(std::shared_ptr<rclcpp::Node>&, node, rclcpp::Time const&,
                      start, rclcpp::Time const&, end, char const*, label),

    LTTNG_UST_TP_FIELDS(lttng_ust_field_string(node_name, node->get_name())
                            lttng_ust_field_float(start_stamp, start.seconds())
                                lttng_ust_field_float(end_stamp, end.seconds())
                                    lttng_ust_field_string(label, label))

)

LTTNG_UST_TRACEPOINT_EVENT_INSTANCE(

    LTTNG_UST_TRACEPOINT_PROVIDER,

    compute_class,

    LTTNG_UST_TRACEPOINT_PROVIDER,

    compute_cpu,

    LTTNG_UST_TP_ARGS(std::shared_ptr<rclcpp::Node>&, node, rclcpp::Time const&,
                      start, rclcpp::Time const&, end, char const*, label)

)

LTTNG_UST_TRACEPOINT_EVENT_INSTANCE(

    LTTNG_UST_TRACEPOINT_PROVIDER,

    compute_class,

    LTTNG_UST_TRACEPOINT_PROVIDER,

    compute_fpga,

    LTTNG_UST_TP_ARGS(std::shared_ptr<rclcpp::Node>&, node, rclcpp::Time const&,
                      start, rclcpp::Time const&, end, char const*, label)

)

LTTNG_UST_TRACEPOINT_LOGLEVEL(LTTNG_UST_TRACEPOINT_PROVIDER, compute_cpu,
                              LTTNG_UST_TRACEPOINT_LOGLEVEL_INFO)

LTTNG_UST_TRACEPOINT_LOGLEVEL(LTTNG_UST_TRACEPOINT_PROVIDER, compute_fpga,
                              LTTNG_UST_TRACEPOINT_LOGLEVEL_INFO)

#endif /* _TP_H */

#include <lttng/tracepoint-event.h>
