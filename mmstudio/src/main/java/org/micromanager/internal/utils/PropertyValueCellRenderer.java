package org.micromanager.internal.utils;

import java.awt.Component;
import java.text.ParseException;
import javax.swing.JLabel;
import javax.swing.JTable;
import javax.swing.table.TableCellRenderer;

public class PropertyValueCellRenderer implements TableCellRenderer {
   // This method is called each time a cell in a column
   // using this renderer needs to be rendered.

   PropertyItem item_;
   JLabel lab_ = new JLabel();
   private boolean disable_;

   public PropertyValueCellRenderer(boolean disable) {
      super();
      disable_ = disable;
   }

   public PropertyValueCellRenderer() {
      this(false);
   }

   @Override
   public Component getTableCellRendererComponent(JTable table, Object value,
           boolean isSelected, boolean hasFocus, int rowIndex, int colIndex) {

      MMPropertyTableModel data = (MMPropertyTableModel) table.getModel();
      item_ = data.getPropertyItem(rowIndex);

      lab_.setOpaque(true);
      lab_.setHorizontalAlignment(JLabel.LEFT);

      Component comp;

      if (item_.hasRange) {
         SliderPanel slider = new SliderPanel();
         if (item_.isInteger()) {
            slider.setLimits((int) item_.lowerLimit, (int) item_.upperLimit);
         } else {
            slider.setLimits(item_.lowerLimit, item_.upperLimit);
         }
         try {
            slider.setText((String) value);
         } catch (ParseException ex) {
            ReportingUtils.logError(ex);
         }
         slider.setToolTipText(item_.value);
         comp = slider;
      } else {
         lab_.setText(item_.value);
         comp = lab_;
      }

      if (item_.readOnly) {
         comp.setBackground(DaytimeNighttime.getInstance().getDisabledBackgroundColor());
         comp.setForeground(DaytimeNighttime.getInstance().getDisabledTextColor());
      } else {
         comp.setBackground(DaytimeNighttime.getInstance().getBackgroundColor());
         comp.setForeground(DaytimeNighttime.getInstance().getEnabledTextColor());
      }

      if (!table.isCellEditable(rowIndex, colIndex)) {
         comp.setEnabled(false);
         // For legibility's sake, we always use the "enabled" color.
         comp.setForeground(DaytimeNighttime.getInstance().getEnabledTextColor());
      } else {
         comp.setEnabled(true);
      }

      return comp;
   }

   // The following methods override the defaults for performance reasons
   public void validate() {
   }

   public void revalidate() {
   }

   protected void firePropertyChange(String propertyName, Object oldValue, Object newValue) {
   }

   public void firePropertyChange(String propertyName, boolean oldValue, boolean newValue) {
   }
}
