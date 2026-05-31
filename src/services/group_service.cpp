#include "services/group_service.h"

#include "repositories/group_repository.h"
#include "repositories/workload_repository.h"
#include "utils/string_utils.h"

namespace services
{
    OperationResult ValidateGroup(const models::Group& group)
    {
        if (utils::IsBlank(group.name))
        {
            return OperationResult::Fail("Назва групи не може бути порожньою.");
        }

        if (group.course == 0 || group.course > 4)
        {
            return OperationResult::Fail("Курс групи повинен бути в межах 1-4.");
        }

        if (utils::IsBlank(group.speciality))
        {
            return OperationResult::Fail("Спецiальнiсть групи не може бути порожньою.");
        }

        return OperationResult::Ok();
    }

    OperationResult CreateGroup(models::Group& group)
    {
        OperationResult validation_result = ValidateGroup(group);
        if (!validation_result.success)
        {
            return validation_result;
        }

        return SaveGroup(group);
    }

    OperationResult UpdateGroup(unsigned short group_id, const models::Group& group)
    {
        if (!GetGroupById(group_id).has_value())
        {
            return OperationResult::Fail("Групу з таким Id не знайдено.");
        }

        OperationResult validation_result = ValidateGroup(group);
        if (!validation_result.success)
        {
            return validation_result;
        }

        return EditGroupById(group_id, group);
    }

    OperationResult DeleteGroup(unsigned short group_id)
    {
        if (!GetGroupById(group_id).has_value())
        {
            return OperationResult::Fail("Групу з таким Id не знайдено.");
        }

        if (HasWorkloadForGroup(group_id))
        {
            return OperationResult::Fail("Група використовується в навантаженнi.");
        }

        return DeleteGroupById(group_id);
    }
}
