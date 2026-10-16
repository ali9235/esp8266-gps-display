# VOLTRA Atlas: security, privacy and safe operation

This research/prototype repository is not certified or penetration tested. Controls below are limited to inspected source. A clean pattern scan does not prove the absence of all secrets or vulnerabilities.

## Assets and trust boundaries

| Threat / asset | Existing control or required handling | Residual risk |
| --- | --- | --- |
| Location disclosure | Do not publish home coordinates, routes or raw private NMEA logs. | Coordinates can be visible to bystanders on a display. |
| Untrusted/stale receiver data | Parser, coordinate bounds and age policy distinguish states. | No GNSS authentication or spoofing/jamming detection. |
| Access and interface | No Wi-Fi transmission; optional input is RX-only. | Serial is unauthenticated; electrical compatibility remains unverified. |

## Keys, permissions and disclosure

Never commit API keys, Wi-Fi credentials, private keys, private addresses or location traces. Use local untracked configuration and placeholders in examples. Rotate previously disclosed credentials; deletion from a working copy does not erase Git history.

The proposed engineering-check workflow uses read-only repository access, no project secrets, no deployment permissions and no physical devices. Review dependency changes. Never disable application-control policy to run a blocked test.

No private vulnerability-reporting channel has been verified for this repository. Do not post working secrets or sensitive exploit details in public issues; use an independently verified private owner contact if available. This file does not claim that branch protection, secret scanning or private reporting has been enabled.

## Media and physical operation

Review frames for faces, serial numbers, locations, network details and open terminals before publication. Preserve actual hardware evidence; never fabricate operation. Power, wiring and physical safety require their own review.

[Technical boundaries](docs/ARCHITECTURE.md) · [Release checklist](docs/RELEASING.md)
