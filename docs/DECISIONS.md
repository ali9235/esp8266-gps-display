# VOLTRA Atlas: engineering decisions

These explain the **current inspectable design/documentation**, not why the owner originally bought components. Original selection history and personal debugging experiences have not been supplied.

| Decision | Current-file rationale | Alternative / trade-off | Constraint |
| --- | --- | --- | --- |
| Freshness before display | Separate byte activity from location age and hide stale positions. | Indefinitely displaying the last fix can mislead. | Age policy does not measure accuracy/integrity. |
| Bounded ingestion | A 96-byte budget leaves time for display and yielding. | Draining continuous input can starve other tasks. | UART capacity and overflow require bench tests. |
| RX-only optional adapter | Avoid undocumented receiver configuration commands. | Configuring rate needs the actual module specification. | No module configuration or antenna result is established. |

## Challenges: distinguish observed from suggested

The tests and configuration guards establish specific reference-software behavior, not proof that those failures occurred on the owner's prototype. The original matching sketch was not recovered.

No satellite acquisition, measured accuracy, antenna/RF result or actual TFT commissioning was established.

Troubleshooting suggestions are hypotheses, not incidents already solved. Add a case study only with the observed symptom, reproducible conditions, evidence for the cause, exact change, before/after test and remaining uncertainty. Do not turn design intentions into measured improvements.

[Architecture](ARCHITECTURE.md) · [Validation record](VALIDATION.md)
