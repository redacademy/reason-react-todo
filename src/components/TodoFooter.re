let str = ReasonReact.string;

let component = ReasonReact.statelessComponent("TodoFooter");

let make = (~onRemoveAll, ~onRemoveCompleted, ~itemCount, _children) => {
  ...component,
  render: _self => {
    let numItems = itemCount;
    let word = numItems === 1 ? " item" : " items";
    <div className="footer">
      <p> (str(string_of_int(numItems) ++ word)) </p>
      <button onClick=((_) => onRemoveCompleted())>
        (str("Remove Completed"))
      </button>
      <button onClick=((_) => onRemoveAll())> (str("Remove All")) </button>
    </div>;
  },
};