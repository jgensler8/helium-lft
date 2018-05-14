# helium-lft : Helium Large File Transfer

helium-lft aims to provide a protocol to transmit larger pieces of data over Helium.

## Use Cases

* Photos of a plant
* Audio snippet of an animal

## API

```
#include <heliumlft.h>

channel_send_lft(&channel, CHANNEL_NAME, buffer, length)
```

This function will send payloads with the following format:

```
<transaction-id>,<packet-number>,<packet-total>,<payload><newline-character>
```

You'll need to have code listening on end of the channel ready to assemble the "packets" into a unified payload.

## Testing

Tests are written with the [ArduinoUnit](https://github.com/mmurdoch/arduinounit) library.
