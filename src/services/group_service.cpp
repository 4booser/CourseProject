#include "services/group_service.h"

#include "repositories/group_repository.h"
#include "repositories/workload_repository.h"

namespace services
{
    OperationResult ValidateGroup(const models::Group& group)
    {
        if (group.name.empty())
        {
            return OperationResult::Fail("Назва групи не може бути порожньою.");
        }

        if (group.course == 0 || group.course > 4)
        {
            return OperationResult::Fail("Курс групи повинен бути в межах 1-4.");
        }

        if (group.speciality.empty())
        {
            return OperationResult::Fail("Спецiальнiсть групи не може бути порожньою.");
        }

        return OperationResult::Ok();
    }

    OperationResult CanDeleteGroup(unsigned short group_id)
    {
        if (!GetGroupById(group_id).has_value())
        {
            return OperationResult::Fail("Групу з таким Id не знайдено.");
        }

        if (HasWorkloadForGroup(group_id))
        {
            return OperationResult::Fail("Неможливо видалити групу: вона використовується в навантаженнi.");
        }

        return OperationResult::Ok();
    }
}
