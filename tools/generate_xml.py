# ─────────────────────────────────────────────
#  AFB - Control One  |  MIDI Mapping Generator
# ─────────────────────────────────────────────

def cue_block(control, deck_id, slot_id, deck_label):
    cue_num = slot_id + 1
    return f"""
  <!-- ── Cue {cue_num} Deck {deck_label} (nota {control}) ── -->
  <control channel="1" event_type="Note On" control="{control}">
    <userio event="click">
      <cue_point deck_set="Default" deck_id="{deck_id}" slot_id="{slot_id}">
        <translation action_on="any" behaviour="explicit"/>
      </cue_point>
    </userio>
    <userio event="output">
      <cue_point_set deck_set="Default" deck_id="{deck_id}" slot_id="{slot_id}">
        <translation action_on="any">
          <alias name="on" value="127"/>
          <alias name="off" value="0"/>
        </translation>
      </cue_point_set>
    </userio>
  </control>"""


def fx_block(control, deck_id, slot_id, deck_label):
    return f"""
  <!-- ── FX {slot_id} Deck {deck_label} (nota {control}) ── -->
  <control channel="1" event_type="Note On" control="{control}">
    <userio event="click">
      <effect_level_1_slot_enable deck_set="DJ Effects" deck_id="{deck_id}" slot_id="{slot_id}">
        <translation action_on="press" behaviour="toggle"/>
      </effect_level_1_slot_enable>
    </userio>
    <userio event="output">
      <effect_level_1_slot_enable deck_set="DJ Effects" deck_id="{deck_id}" slot_id="{slot_id}">
        <translation action_on="any">
          <alias name="on" value="127"/>
          <alias name="off" value="0"/>
        </translation>
      </effect_level_1_slot_enable>
    </userio>
  </control>"""


def pot_block(control, deck_id, deck_label, pot_num):
    single_param = f"effect_slot_parameter_{pot_num}"
    multi_param  = "effect_level_1_slot_parameter_1"
    multi_slot   = pot_num

    return f"""
  <!-- ── POT {pot_num} Deck {deck_label} (CC {control}) ── -->
  <control channel="1" event_type="Control Change" data_type="Absolute 7" control="{control}">
    <case>
      <condition>
        <effect_bank_mode deck_set="DJ Effects" deck_id="{deck_id}" slot_id="0" operator="equal" cmp_value="Single Mode"/>
      </condition>
      <userio event="click">
        <{single_param} deck_set="DJ Effects" deck_id="{deck_id}" slot_id="0">
          <translation action_on="any" behaviour="explicit"/>
        </{single_param}>
      </userio>
    </case>
    <case>
      <condition>
        <effect_bank_mode deck_set="DJ Effects" deck_id="{deck_id}" slot_id="0" operator="equal" cmp_value="Multi Mode"/>
      </condition>
      <userio event="click">
        <{multi_param} deck_set="DJ Effects" deck_id="{deck_id}" slot_id="{multi_slot}">
          <translation action_on="any" behaviour="explicit"/>
        </{multi_param}>
      </userio>
    </case>
  </control>"""


def tap_tempo_block(control, deck_id, deck_label):
    return f"""
  <!-- ── Tap Tempo Deck {deck_label} (CC {control}) ── -->
  <control channel="1" event_type="Control Change" control="{control}">
    <userio event="click">
      <effect_bank_tap_tempo deck_set="DJ Effects" deck_id="{deck_id}" slot_id="0">
        <translation action_on="any" behaviour="explicit"/>
      </effect_bank_tap_tempo>
    </userio>
  </control>"""



output = []
output.append('<?xml version="1.0" encoding="UTF-8"?>')
output.append('<midi app="2.5.5.83">')

output.append('\n  <!-- =========== Cues Deck L =========== -->')
for i in range(8): output.append(cue_block(36 + i, 0, i, "L"))

output.append('\n  <!-- =========== Cues Deck R =========== -->')
for i in range(8): output.append(cue_block(44 + i, 1, i, "R"))

output.append('\n  <!-- =========== FX Deck L =========== -->')
for i in range(3): output.append(fx_block(52 + i, 0, i + 1, "L"))

output.append('\n  <!-- =========== FX Deck R =========== -->')
for i in range(3): output.append(fx_block(55 + i, 1, i + 1, "R"))

output.append('\n  <!-- =========== POTs Deck L =========== -->')
for i in range(3): output.append(pot_block(1 + i, 0, "L", i + 1))

output.append('\n  <!-- =========== POTs Deck R =========== -->')
for i in range(3): output.append(pot_block(4 + i, 1, "R", i + 1))

output.append('\n  <!-- =========== Tap Tempo =========== -->')
output.append(tap_tempo_block(27, 0, "L"))
output.append(tap_tempo_block(35, 1, "R"))

output.append('\n</midi>')
print('\n'.join(output))