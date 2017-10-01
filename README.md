README
======

- Get Temperature
```
$ dbus-send --system --dest=org.warp7.service.mpl3115 --print-reply --type=method_call / local.ServiceMPL3115.CServiceMPL3115.getTemperature
```

- Set Loop status
```
$ dbus-send --system --dest=org.warp7.service.mpl3115 --print-reply --type=method_call / local.ServiceMPL3115.CServiceMPL3115.enableLoop boolean:true
```

- Get Loop status
```
$ dbus-send --system --dest=org.warp7.service.mpl3115 --print-reply --type=method_call / local.ServiceMPL3115.CServiceMPL3115.loopIsEnabled
```
