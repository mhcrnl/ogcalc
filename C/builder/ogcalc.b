<?xml version="1.0"?>
<interface>
  <!-- interface-requires gtk+ 2.6 -->
  <!-- interface-naming-policy toplevel-contextual -->
  <object class="GtkWindow" id="ogcalc_main_window">
    <property name="title" translatable="yes">OG &amp; ABV Calculator</property>
    <property name="resizable">False</property>
    <signal name="destroy" handler="gtk_main_quit"/>
    <child>
      <object class="GtkVBox" id="vbox1">
        <property name="visible">True</property>
        <property name="orientation">vertical</property>
        <child>
          <object class="GtkVBox" id="vbox2">
            <property name="visible">True</property>
            <property name="border_width">10</property>
            <property name="orientation">vertical</property>
            <property name="spacing">5</property>
            <property name="homogeneous">True</property>
            <child>
              <object class="GtkHBox" id="hbox1">
                <property name="visible">True</property>
                <property name="spacing">10</property>
                <child>
                  <object class="GtkHBox" id="hbox2">
                    <property name="visible">True</property>
                    <property name="spacing">5</property>
                    <child>
                      <object class="GtkEventBox" id="eventbox1">
                        <property name="visible">True</property>
                        <child>
                          <object class="GtkLabel" id="label1">
                            <property name="visible">True</property>
                            <property name="label" translatable="yes">PG:</property>
                          </object>
                        </child>
                      </object>
                      <packing>
                        <property name="expand">False</property>
                        <property name="fill">False</property>
                        <property name="position">0</property>
                      </packing>
                    </child>
                    <child>
                      <object class="GtkSpinButton" id="pg_entry">
                        <property name="visible">True</property>
                        <property name="can_focus">True</property>
                        <property name="adjustment"></property>
                        <property name="climb_rate">0.5</property>
                        <property name="digits">2</property>
                        <signal name="activate" handler="gtk_widget_grab_focus" object="ri_entry"/>
                      </object>
                      <packing>
                        <property name="position">1</property>
                      </packing>
                    </child>
                  </object>
                  <packing>
                    <property name="position">0</property>
                  </packing>
                </child>
                <child>
                  <object class="GtkHBox" id="hbox3">
                    <property name="visible">True</property>
                    <property name="spacing">5</property>
                    <child>
                      <object class="GtkEventBox" id="eventbox2">
                        <property name="visible">True</property>
                        <child>
                          <object class="GtkLabel" id="ri_entry">
                            <property name="visible">True</property>
                            <property name="label" translatable="yes">RI:</property>
                          </object>
                        </child>
                      </object>
                      <packing>
                        <property name="expand">False</property>
                        <property name="fill">False</property>
                        <property name="position">0</property>
                      </packing>
                    </child>
                    <child>
                      <object class="GtkSpinButton" id="ri_entry1">
                        <property name="visible">True</property>
                        <property name="can_focus">True</property>
                        <property name="adjustment"></property>
                        <property name="climb_rate">0.5</property>
                        <property name="digits">2</property>
                        <signal name="activate" handler="gtk_widget_grab_focus" object="cf_entry"/>
                      </object>
                      <packing>
                        <property name="position">1</property>
                      </packing>
                    </child>
                  </object>
                  <packing>
                    <property name="position">1</property>
                  </packing>
                </child>
                <child>
                  <object class="GtkHBox" id="hbox4">
                    <property name="visible">True</property>
                    <property name="spacing">5</property>
                    <child>
                      <object class="GtkEventBox" id="eventbox3">
                        <property name="visible">True</property>
                        <child>
                          <object class="GtkLabel" id="cf_entry">
                            <property name="visible">True</property>
                            <property name="label" translatable="yes">CF:</property>
                          </object>
                        </child>
                      </object>
                      <packing>
                        <property name="expand">False</property>
                        <property name="fill">False</property>
                        <property name="position">0</property>
                      </packing>
                    </child>
                    <child>
                      <object class="GtkSpinButton" id="cf_entry1">
                        <property name="visible">True</property>
                        <property name="can_focus">True</property>
                        <property name="adjustment"></property>
                        <property name="climb_rate">0.20000000000000001</property>
                        <property name="digits">1</property>
                        <signal name="activate" handler="gtk_window_activate_default" object="ogcalc_main_window"/>
                      </object>
                      <packing>
                        <property name="position">1</property>
                      </packing>
                    </child>
                  </object>
                  <packing>
                    <property name="position">2</property>
                  </packing>
                </child>
              </object>
              <packing>
                <property name="position">0</property>
              </packing>
            </child>
            <child>
              <object class="GtkHBox" id="hbox5">
                <property name="visible">True</property>
                <property name="spacing">10</property>
                <property name="homogeneous">True</property>
                <child>
                  <object class="GtkHBox" id="hbox6">
                    <property name="visible">True</property>
                    <property name="spacing">5</property>
                    <child>
                      <object class="GtkEventBox" id="eventbox4">
                        <property name="visible">True</property>
                        <child>
                          <object class="GtkLabel" id="label4">
                            <property name="visible">True</property>
                            <property name="label" translatable="yes">OG:</property>
                          </object>
                        </child>
                      </object>
                      <packing>
                        <property name="expand">False</property>
                        <property name="fill">False</property>
                        <property name="position">0</property>
                      </packing>
                    </child>
                    <child>
                      <object class="GtkLabel" id="og_result">
                        <property name="visible">True</property>
                      </object>
                      <packing>
                        <property name="position">1</property>
                      </packing>
                    </child>
                  </object>
                  <packing>
                    <property name="position">0</property>
                  </packing>
                </child>
                <child>
                  <object class="GtkHBox" id="hbox7">
                    <property name="visible">True</property>
                    <property name="spacing">5</property>
                    <child>
                      <object class="GtkEventBox" id="eventbox5">
                        <property name="visible">True</property>
                        <child>
                          <object class="GtkLabel" id="label6">
                            <property name="visible">True</property>
                            <property name="label" translatable="yes">ABV %:</property>
                          </object>
                        </child>
                      </object>
                      <packing>
                        <property name="expand">False</property>
                        <property name="fill">False</property>
                        <property name="position">0</property>
                      </packing>
                    </child>
                    <child>
                      <object class="GtkLabel" id="abv_result">
                        <property name="visible">True</property>
                      </object>
                      <packing>
                        <property name="position">1</property>
                      </packing>
                    </child>
                  </object>
                  <packing>
                    <property name="position">1</property>
                  </packing>
                </child>
              </object>
              <packing>
                <property name="position">1</property>
              </packing>
            </child>
          </object>
          <packing>
            <property name="position">0</property>
          </packing>
        </child>
        <child>
          <object class="GtkHSeparator" id="hseparator1">
            <property name="visible">True</property>
          </object>
          <packing>
            <property name="expand">False</property>
            <property name="fill">False</property>
            <property name="position">1</property>
          </packing>
        </child>
        <child>
          <object class="GtkHBox" id="hbox8">
            <property name="visible">True</property>
            <property name="border_width">10</property>
            <property name="spacing">5</property>
            <property name="homogeneous">True</property>
            <child>
              <object class="GtkButton" id="quit_button">
                <property name="label">gtk-quit</property>
                <property name="visible">True</property>
                <property name="can_focus">True</property>
                <property name="receives_default">False</property>
                <property name="use_stock">True</property>
                <signal name="clicked" handler="gtk_main_quit"/>
              </object>
              <packing>
                <property name="position">0</property>
              </packing>
            </child>
            <child>
              <object class="GtkButton" id="reset_button">
                <property name="label" translatable="yes">_Reset</property>
                <property name="visible">True</property>
                <property name="can_focus">True</property>
                <property name="can_default">True</property>
                <property name="receives_default">False</property>
                <property name="use_underline">True</property>
                <signal name="clicked" handler="on_button_clicked_reset"/>
                <signal name="clicked" handler="gtk_widget_grab_focus" object="pg_entry"/>
              </object>
              <packing>
                <property name="position">1</property>
              </packing>
            </child>
            <child>
              <object class="GtkButton" id="calculate_button">
                <property name="label" translatable="yes">_Calculate</property>
                <property name="visible">True</property>
                <property name="can_focus">True</property>
                <property name="can_default">True</property>
                <property name="has_default">True</property>
                <property name="receives_default">False</property>
                <property name="use_underline">True</property>
                <signal name="clicked" handler="on_button_clicked_calculate"/>
                <signal name="clicked" handler="gtk_widget_grab_focus" object="reset_button"/>
              </object>
              <packing>
                <property name="position">2</property>
              </packing>
            </child>
          </object>
          <packing>
            <property name="position">2</property>
          </packing>
        </child>
      </object>
    </child>
  </object>
</interface>
