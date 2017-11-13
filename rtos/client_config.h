// AWS IoT client endpoint
const char *client_endpoint = "a21jd7gud1swyd.iot.us-east-1.amazonaws.com";

// AWS IoT device certificate (ECC)
const char *client_cert =
"-----BEGIN CERTIFICATE-----\r\n"
"MIIDFTCCAf2gAwIBAgIUYuiKI3pB1OHyMvUjNv/SnskSR08wDQYJKoZIhvcNAQEL\r\n"
"BQAwTTFLMEkGA1UECwxCQW1hem9uIFdlYiBTZXJ2aWNlcyBPPUFtYXpvbi5jb20g\r\n"
"SW5jLiBMPVNlYXR0bGUgU1Q9V2FzaGluZ3RvbiBDPVVTMB4XDTE3MTAzMDA5MjQx\r\n"
"MVoXDTQ5MTIzMTIzNTk1OVowgaQxCzAJBgNVBAYTAlRIMRMwEQYDVQQIDApDaGlh\r\n"
"bmcgTWFpMRMwEQYDVQQHDApDaGlhbmcgTWFpMRkwFwYDVQQKDBBGb3JtaW5hIFNv\r\n"
"ZnR3YXJlMRAwDgYDVQQLDAdJVCBEZXB0MRYwFAYDVQQDDA1Kb2huIEtvc2luc2tp\r\n"
"MSYwJAYJKoZIhvcNAQkBFhdqb2huLmtvc2luc2tpQGdtYWlsLmNvbTBZMBMGByqG\r\n"
"SM49AgEGCCqGSM49AwEHA0IABLSXtzFfRthJCQMJ9syJLU2uAH4EI6DxoylW7Fb8\r\n"
"B7JAmFVunOcFpE388qM6DkVF9HwhtEPBhSFpK3W4yRcYTnWjYDBeMB8GA1UdIwQY\r\n"
"MBaAFIcvND4YEnwNRLP0RUeYrDHDbPsgMB0GA1UdDgQWBBRuLn4ULtnM+HlkxPIw\r\n"
"TW/HyewtJDAMBgNVHRMBAf8EAjAAMA4GA1UdDwEB/wQEAwIHgDANBgkqhkiG9w0B\r\n"
"AQsFAAOCAQEAdcjbrDGvMn21KOcSYiOj6PgERdDBj2FMdFW7l7go9Y+ggE4lQXtP\r\n"
"C3l9Sqh28nc8U5ZU/Pi7UfYjuqbs2X2oFqEs8Jg0ANdA77xnsnmSKnU5/jAJVORi\r\n"
"knP/kd+6EHPiRBsjeGyPWowZWfALQaOpz76tMxG/7xNH6l0EMba2DgtVsLPfqVjA\r\n"
"a03tfGM+9lCeyAZPK0husVYxUri2Q1LciINSrLh6zGw42/WY36S/jMEdyyZ0j8KI\r\n"
"MEupvwgCKT+ZSVtmFwUC4M28B1DdaDkvo+HxL2ByuyPQFyNaYHVaIq2BDDLu1Uqr\r\n"
"zkpD+1ZetpB7gZv9Ec9fZ/eAJC6H7+NvPQ==\r\n"
"-----END CERTIFICATE-----\r\n"; 

// AWS IoT device private key (ECC)
const char *client_key = 
"-----BEGIN EC PARAMETERS-----\r\n"
"BggqhkjOPQMBBw==\r\n"
"-----END EC PARAMETERS-----\r\n"
"-----BEGIN EC PRIVATE KEY-----\r\n"
"MHYCAQEEH+Ki3lwjEp++3TMcPugyboBGuulaLl+z/NRtxiKfIIOgCgYIKoZIzj0D\r\n"
"AQehRANCAAS0l7cxX0bYSQkDCfbMiS1NrgB+BCOg8aMpVuxW/AeyQJhVbpznBaRN\r\n"
"/PKjOg5FRfR8IbRDwYUhaSt1uMkXGE51\r\n"
"-----END EC PRIVATE KEY-----\r\n"; 


// trusted root CA certificate - https://www.symantec.com/content/en/us/enterprise/verisign/roots/VeriSign-Class%203-Public-Primary-Certification-Authority-G5.pem
const char *ca_cert = "-----BEGIN CERTIFICATE-----\r\n"
        "MIIE0zCCA7ugAwIBAgIQGNrRniZ96LtKIVjNzGs7SjANBgkqhkiG9w0BAQUFADCB\r\n"
        "yjELMAkGA1UEBhMCVVMxFzAVBgNVBAoTDlZlcmlTaWduLCBJbmMuMR8wHQYDVQQL\r\n"
        "ExZWZXJpU2lnbiBUcnVzdCBOZXR3b3JrMTowOAYDVQQLEzEoYykgMjAwNiBWZXJp\r\n"
        "U2lnbiwgSW5jLiAtIEZvciBhdXRob3JpemVkIHVzZSBvbmx5MUUwQwYDVQQDEzxW\r\n"
        "ZXJpU2lnbiBDbGFzcyAzIFB1YmxpYyBQcmltYXJ5IENlcnRpZmljYXRpb24gQXV0\r\n"
        "aG9yaXR5IC0gRzUwHhcNMDYxMTA4MDAwMDAwWhcNMzYwNzE2MjM1OTU5WjCByjEL\r\n"
        "MAkGA1UEBhMCVVMxFzAVBgNVBAoTDlZlcmlTaWduLCBJbmMuMR8wHQYDVQQLExZW\r\n"
        "ZXJpU2lnbiBUcnVzdCBOZXR3b3JrMTowOAYDVQQLEzEoYykgMjAwNiBWZXJpU2ln\r\n"
        "biwgSW5jLiAtIEZvciBhdXRob3JpemVkIHVzZSBvbmx5MUUwQwYDVQQDEzxWZXJp\r\n"
        "U2lnbiBDbGFzcyAzIFB1YmxpYyBQcmltYXJ5IENlcnRpZmljYXRpb24gQXV0aG9y\r\n"
        "aXR5IC0gRzUwggEiMA0GCSqGSIb3DQEBAQUAA4IBDwAwggEKAoIBAQCvJAgIKXo1\r\n"
        "nmAMqudLO07cfLw8RRy7K+D+KQL5VwijZIUVJ/XxrcgxiV0i6CqqpkKzj/i5Vbex\r\n"
        "t0uz/o9+B1fs70PbZmIVYc9gDaTY3vjgw2IIPVQT60nKWVSFJuUrjxuf6/WhkcIz\r\n"
        "SdhDY2pSS9KP6HBRTdGJaXvHcPaz3BJ023tdS1bTlr8Vd6Gw9KIl8q8ckmcY5fQG\r\n"
        "BO+QueQA5N06tRn/Arr0PO7gi+s3i+z016zy9vA9r911kTMZHRxAy3QkGSGT2RT+\r\n"
        "rCpSx4/VBEnkjWNHiDxpg8v+R70rfk/Fla4OndTRQ8Bnc+MUCH7lP59zuDMKz10/\r\n"
        "NIeWiu5T6CUVAgMBAAGjgbIwga8wDwYDVR0TAQH/BAUwAwEB/zAOBgNVHQ8BAf8E\r\n"
        "BAMCAQYwbQYIKwYBBQUHAQwEYTBfoV2gWzBZMFcwVRYJaW1hZ2UvZ2lmMCEwHzAH\r\n"
        "BgUrDgMCGgQUj+XTGoasjY5rw8+AatRIGCx7GS4wJRYjaHR0cDovL2xvZ28udmVy\r\n"
        "aXNpZ24uY29tL3ZzbG9nby5naWYwHQYDVR0OBBYEFH/TZafC3ey78DAJ80M5+gKv\r\n"
        "MzEzMA0GCSqGSIb3DQEBBQUAA4IBAQCTJEowX2LP2BqYLz3q3JktvXf2pXkiOOzE\r\n"
        "p6B4Eq1iDkVwZMXnl2YtmAl+X6/WzChl8gGqCBpH3vn5fJJaCGkgDdk+bW48DW7Y\r\n"
        "5gaRQBi5+MHt39tBquCWIMnNZBU4gcmU7qKEKQsTb47bDN0lAtukixlE0kF6BWlK\r\n"
        "WE9gyn6CagsCqiUXObXbf+eEZSqVir2G3l6BFoMtEMze/aiCKm0oHw0LxOXnGiYZ\r\n"
        "4fQRbxC1lfznQgUy286dUV4otp6F01vvpX1FQHKOtw5rDgb7MzVIcbidJ4vEZV8N\r\n"
        "hnacRHr2lVz2XTIIM6RUthg/aFzyQkqFOFSDX9HoLPKsEdao7WNq\r\n"
        "-----END CERTIFICATE-----\r\n";
