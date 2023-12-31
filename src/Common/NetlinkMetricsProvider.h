#pragma once

#include <sys/types.h>
#include <base/types.h>
#include <boost/noncopyable.hpp>

struct taskstats;

namespace DB
{

/// Get taskstat info from OS kernel via Netlink protocol.
///
/// NOTE: unlike procfs interface, netlink interface, rounds some values to KiBs [1].
///
///   [1]: https://elixir.bootlin.com/linux/v5.18-rc4/source/kernel/tsacct.c#L101
///
class NetlinkMetricsProvider : private boost::noncopyable
{
public:
    NetlinkMetricsProvider();
    ~NetlinkMetricsProvider();

    void getStat(::taskstats & out_stats, pid_t tid) const;

    /// Whether the current process has permissions (sudo or cap_net_admin capabilities) to get taskstats info
    static bool checkPermissions();

#if defined(OS_LINUX)
private:
    int netlink_socket_fd = -1;
    UInt16 taskstats_family_id = 0;
#endif
};

}
