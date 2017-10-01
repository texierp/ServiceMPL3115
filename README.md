README
======

```
$ dbus-send --system --dest=org.warp7.service.mpl3115 --print-reply --type=method_call / local.ServiceMPL3115.CServiceMPL3115.getTemperature
```

```
dbus-send --system --dest=org.warp7.service.mpl3115 --print-reply --type=method_call / local.ServiceMPL3115.CServiceMPL3115.enableLoop boolean:true
```

```
dbus-send --system --dest=org.warp7.service.mpl3115 --print-reply --type=method_call / local.ServiceMPL3115.CServiceMPL3115.loopIsEnabled
```
